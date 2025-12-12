#define _GNU_SOURCE
#include <wayland-client.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/memfd.h>
#include <sys/syscall.h>

#include <cairo/cairo.h>

/* generated xdg-shell header (must exist in project) */
#include "xdg-shell.h"

/* --- xdg_wm_base ping/pong --- */
static void xdg_wm_base_ping(void *data, struct xdg_wm_base *base, uint32_t serial) {
    xdg_wm_base_pong(base, serial);
}
static const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping
};

/* --- globals from registry --- */
static struct wl_compositor *compositor = NULL;
static struct wl_shm        *shm = NULL;
static struct xdg_wm_base   *xdg_wm_base = NULL;

/* --- registry listener --- */
static void registry_global(void *data, struct wl_registry *registry,
                            uint32_t id, const char *interface, uint32_t version) {
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 4);
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        shm = wl_registry_bind(registry, id, &wl_shm_interface, 1);
    } else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
        xdg_wm_base = wl_registry_bind(registry, id, &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(xdg_wm_base, &xdg_wm_base_listener, NULL);
    }
}
static void registry_global_remove(void *data, struct wl_registry *registry, uint32_t id) {}
static const struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove
};

/* --- helper: create shm fd (memfd_create fallback to mkstemp) --- */
static int create_shm_file(size_t size) {
    int fd = -1;
#ifdef MFD_CLOEXEC
    fd = syscall(SYS_memfd_create, "wayland-shm", MFD_CLOEXEC);
    if (fd >= 0) {
        if (ftruncate(fd, size) < 0) { close(fd); return -1; }
        return fd;
    }
#endif
    char tmpl[] = "/tmp/wayland-shm-XXXXXX";
    fd = mkstemp(tmpl);
    if (fd < 0) return -1;
    unlink(tmpl);
    if (ftruncate(fd, size) < 0) { close(fd); return -1; }
    return fd;
}

/* --- xdg_surface configure listener: must ack configure before using buffer --- */
static void xdg_surface_configure(void *data, struct xdg_surface *xdg_surface, uint32_t serial) {
    xdg_surface_ack_configure(xdg_surface, serial);
}
static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_configure
};

int main(int argc, char **argv) {
    const int width = 480;
    const int height = 320;

    struct wl_display *display = wl_display_connect(NULL);
    if (!display) {
        fprintf(stderr, "Unable to connect to Wayland display\n");
        return 1;
    }

    /* bind globals */
    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);

    /* sync to receive globals */
    wl_display_roundtrip(display);

    if (!compositor || !shm || !xdg_wm_base) {
        fprintf(stderr, "Missing required globals: compositor=%p shm=%p xdg_wm_base=%p\n",
                (void*)compositor, (void*)shm, (void*)xdg_wm_base);
        return 1;
    }

    /* prepare SHM buffer */
    int stride = width * 4; /* 4 bytes per pixel ARGB8888 */
    int size = stride * height;
    int fd = create_shm_file(size);
    if (fd < 0) { perror("create_shm_file"); return 1; }

    void *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) { perror("mmap"); close(fd); return 1; }

    /* create pool and buffer */
    struct wl_shm_pool *pool = wl_shm_create_pool(shm, fd, size);
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0, width, height, stride, WL_SHM_FORMAT_ARGB8888);
    wl_shm_pool_destroy(pool);
    /* close original fd; pool keeps its own reference */
    close(fd);

    /* Initially fill background with opaque blue (A R G B: 0xFF2040A0) */
    uint32_t *pix = (uint32_t *)data;
    uint32_t bg = 0xFF2040A0u;
    for (int i = 0; i < width * height; ++i) pix[i] = bg;

    /* Create Cairo surface that wraps the SHM data */
    cairo_surface_t *c_surface = cairo_image_surface_create_for_data(
        (unsigned char *)data,
        CAIRO_FORMAT_ARGB32,
        width,
        height,
        stride
    );
    if (cairo_surface_status(c_surface) != CAIRO_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to create Cairo surface\n");
        munmap(data, size);
        wl_buffer_destroy(buffer);
        return 1;
    }

    cairo_t *cr = cairo_create(c_surface);
    if (cairo_status(cr) != CAIRO_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to create Cairo context\n");
        cairo_surface_destroy(c_surface);
        munmap(data, size);
        wl_buffer_destroy(buffer);
        return 1;
    }

    /* Draw some text onto the buffer using Cairo */
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 36.0);
    /* white text with slight drop shadow */
    cairo_set_source_rgba(cr, 0, 0, 0, 0.6); /* shadow */
    cairo_move_to(cr, 52, 102);
    cairo_show_text(cr, "Hello Wayland!");
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); /* main text */
    cairo_move_to(cr, 50, 100);
    cairo_show_text(cr, "Hello Wayland!");

    /* flush cairo drawing to the image surface */
    cairo_surface_flush(c_surface);

    /* create surface */
    struct wl_surface *surface = wl_compositor_create_surface(compositor);
    if (!surface) { fprintf(stderr,"Failed create surface\n"); return 1; }

    /* create xdg surface / toplevel and ack configure before using buffer */
    struct xdg_surface *xdg_surf = xdg_wm_base_get_xdg_surface(xdg_wm_base, surface);
    xdg_surface_add_listener(xdg_surf, &xdg_surface_listener, NULL);
    struct xdg_toplevel *toplevel = xdg_surface_get_toplevel(xdg_surf);
    xdg_toplevel_set_title(toplevel, "Wayland SHM Cairo");

    /* commit empty surface to trigger configure and wait */
    wl_surface_commit(surface);
    wl_display_roundtrip(display);

    /* attach buffer and commit */
    wl_surface_attach(surface, buffer, 0, 0);
    wl_surface_damage(surface, 0, 0, width, height);
    wl_surface_commit(surface);
    wl_display_flush(display);

    printf("Wayland SHM Cairo surface rendered successfully.\n");

    /* Event loop: keep window visible until killed (Ctrl+C) */
    while (wl_display_dispatch(display) != -1) {
        /* If you want to update text/graphics, create new Cairo drawing here,
           call cairo_surface_flush(c_surface), then attach+commit again. */
    }

    /* cleanup (not normally reached) */
    cairo_destroy(cr);
    cairo_surface_destroy(c_surface);
    munmap(data, size);
    wl_buffer_destroy(buffer);
    wl_surface_destroy(surface);
    wl_display_disconnect(display);
    return 0;
}
