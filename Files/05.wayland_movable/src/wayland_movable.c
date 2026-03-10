/////////////////////////////////////////////////////////////////////////////////////////////////
//            KwiWi ( Kwin Widget - Wayland SHM + Cairo with window moving)
/////////////////////////////////////////////////////////////////////////////////////////////////

/* This file contains the main application logic:
 *  - Wayland connection and global object setup
 *  - xdg-shell toplevel creation
 *  - shared memory (wl_shm) buffer management
 *  - double buffering
 *  - Cairo-based rendering
 *  - event-driven main loop with a periodic "tick"
 *  - INTERACTIVE WINDOW MOVING via xdg_move module
 */

#define _GNU_SOURCE

/*---------------------------------------------------------------------------------------------*/
// * Standard / system headers
/*---------------------------------------------------------------------------------------------*/

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
#include <time.h>
#include <stdbool.h>
#include <poll.h>
#include <signal.h>

#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
// * Project headers
/*---------------------------------------------------------------------------------------------*/

/* generated xdg-shell header (must be present in project) */
#include "xdg-shell.h"

/* XDG window moving helper */
#include "xdg_move.h"

#include "orchestrator/draw_orchestrator.h"

#include "config/config_types.h"
#include "config/config_loader.h"
/*---------------------------------------------------------------------------------------------*/
//  Global state
/*---------------------------------------------------------------------------------------------*/

/* Wayland globals obtained from the registry */
static struct wl_compositor *compositor = NULL;
static struct wl_shm        *shm = NULL;
static struct xdg_wm_base   *xdg_wm_base = NULL;
static struct wl_seat       *seat = NULL;

/*---------------------------------------------------------------------------------------------*/
//  Signal handling
/*---------------------------------------------------------------------------------------------*/

/* Allows clean shutdown via Ctrl+C or SIGTERM */
static volatile sig_atomic_t running = 1;
static void sigint_handler(int sig) {
    (void)sig;
    running = 0;
}

/*---------------------------------------------------------------------------------------------*/
// * xdg_wm_base ping / pong
/*---------------------------------------------------------------------------------------------*/

/* Required by xdg-shell to keep the client responsive */
static void xdg_wm_base_ping(void *data,
                             struct xdg_wm_base *base,
                             uint32_t serial)
{
    (void)data;
    xdg_wm_base_pong(base, serial);
}

static const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping
};

/*---------------------------------------------------------------------------------------------*/
// Registry handling
/*---------------------------------------------------------------------------------------------*/

/*
 * Called once per advertised global object.
 * We bind to the ones we need:
 *  - wl_compositor
 *  - wl_shm
 *  - xdg_wm_base
 *  - wl_seat (for input events)
 */
static void registry_global(void *data,
                            struct wl_registry *registry,
                            uint32_t id,
                            const char *interface,
                            uint32_t version)
{
    (void)data;
    (void)version;

    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        compositor = wl_registry_bind(registry, id,
                                      &wl_compositor_interface, 4);
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        shm = wl_registry_bind(registry, id,
                               &wl_shm_interface, 1);
    } else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
        xdg_wm_base = wl_registry_bind(registry, id,
                                       &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(xdg_wm_base,
                                 &xdg_wm_base_listener, NULL);
    } else if (strcmp(interface, wl_seat_interface.name) == 0) {
        seat = wl_registry_bind(registry, id,
                               &wl_seat_interface, 1);
    }
}

static void registry_global_remove(void *data,
                                   struct wl_registry *registry,
                                   uint32_t id)
{
    (void)data;
    (void)registry;
    (void)id;
}

static const struct wl_registry_listener registry_listener = {
    .global        = registry_global,
    .global_remove = registry_global_remove
};

/*---------------------------------------------------------------------------------------------*/
//  Shared memory helper
/*---------------------------------------------------------------------------------------------*/

/*
 * Creates an anonymous file descriptor suitable for wl_shm.
 * Uses memfd_create() when available, otherwise mkstemp().
 */
static int create_shm_file(size_t size)
{
    int fd = -1;

#ifdef MFD_CLOEXEC
    fd = syscall(SYS_memfd_create, "wayland-shm", MFD_CLOEXEC);
    if (fd >= 0) {
        if (ftruncate(fd, size) < 0) {
            close(fd);
            return -1;
        }
        return fd;
    }
#endif

    char tmpl[] = "/tmp/wayland-shm-XXXXXX";
    fd = mkstemp(tmpl);
    if (fd < 0)
        return -1;

    unlink(tmpl);
    if (ftruncate(fd, size) < 0) {
        close(fd);
        return -1;
    }

    return fd;
}

/*---------------------------------------------------------------------------------------------*/
//  xdg_surface configure
/*---------------------------------------------------------------------------------------------*/

/*
 * Must ACK every configure event before attaching a buffer.
 */
static void xdg_surface_configure(void *data,
                                  struct xdg_surface *xdg_surface,
                                  uint32_t serial)
{
    (void)data;
    xdg_surface_ack_configure(xdg_surface, serial);
}

static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_configure
};

/*---------------------------------------------------------------------------------------------*/
//  SHM buffer abstraction
/*---------------------------------------------------------------------------------------------*/

/*
 * Represents one shared-memory buffer used for rendering.
 * Two of these are used for double buffering.
 */
struct shm_buffer {
    void *data;                 /* mmap() pointer */
    size_t size;                /* size of mapped region */
    cairo_surface_t *c_surface; /* Cairo surface wrapping SHM */
    struct wl_buffer *buffer;   /* Wayland buffer object */
    bool busy;                  /* true while compositor uses it */
};

/*---------------------------------------------------------------------------------------------*/
// wl_buffer release handler
/*---------------------------------------------------------------------------------------------*/

/*
 * Called by the compositor when it no longer needs the buffer.
 * Marks the buffer as reusable.
 */
static void buffer_release(void *data,
                           struct wl_buffer *wl_buffer)
{
    (void)wl_buffer;
    struct shm_buffer *b = data;
    if (b)
        b->busy = false;
}

static const struct wl_buffer_listener buffer_listener = {
    .release = buffer_release
};

/*---------------------------------------------------------------------------------------------*/
//     * M A I N *
/*---------------------------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

/*---------------------------------------------------------------------------------------------*/
//     * WINDOW / BUFFER GEOMETRY *
/*---------------------------------------------------------------------------------------------*/
    config_load_all();

    printf("DEBUG: window size = %d x %d\n",
       g_config.surface_window.width,
       g_config.surface_window.height);

    const int width  = g_config.surface_window.width;
    const int height = g_config.surface_window.height;
    const int stride = width * 4; /* ARGB8888 */
    const size_t size = (size_t)stride * (size_t)height;


/*---------------------------------------------------------------------------------------------*/
//      Signal handling
/*---------------------------------------------------------------------------------------------*/

    signal(SIGINT,  sigint_handler);
    signal(SIGTERM, sigint_handler);

/*---------------------------------------------------------------------------------------------*/
//     * Wayland connection
/*---------------------------------------------------------------------------------------------*/

    struct wl_display *display = wl_display_connect(NULL);
    if (!display) {
        fprintf(stderr, "Unable to connect to Wayland display\n");
        return 1;
    }

    /* Obtain global objects via registry */
    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(display);

    if (!compositor || !shm || !xdg_wm_base) {
        fprintf(stderr,
                "Missing globals: compositor=%p shm=%p xdg_wm_base=%p\n",
                (void*)compositor, (void*)shm, (void*)xdg_wm_base);
        wl_display_disconnect(display);
        return 1;
    }

    /* Seat is optional but needed for moving */
    if (!seat) {
        fprintf(stderr, "Warning: No wl_seat found - window moving disabled\n");
    }

/*---------------------------------------------------------------------------------------------*/
//      Surface & toplevel
/*---------------------------------------------------------------------------------------------*/

    struct wl_surface *surface = wl_compositor_create_surface(compositor);
    if (!surface) {
        fprintf(stderr, "Failed to create wl_surface\n");
        wl_display_disconnect(display);
        return 1;
    }

    struct xdg_surface *xdg_surf =
        xdg_wm_base_get_xdg_surface(xdg_wm_base, surface);
    xdg_surface_add_listener(xdg_surf,
                             &xdg_surface_listener, NULL);

    struct xdg_toplevel *toplevel =
        xdg_surface_get_toplevel(xdg_surf);
    
    /* Initialize window moving module */
    if (seat) {
        if (xdg_move_init(seat, toplevel) != 0) {
            fprintf(stderr, "Warning: Failed to initialize window moving\n");
        }
        /* Need to roundtrip to get seat capabilities */
        wl_display_roundtrip(display);
    }
    
    xdg_toplevel_set_title(toplevel,
                           "Wayland SHM Cairo (movable)");

    /* Initial commit triggers configure */
    wl_surface_commit(surface);
    wl_display_roundtrip(display);

/*---------------------------------------------------------------------------------------------*/
//     Double-buffer creation
/*---------------------------------------------------------------------------------------------*/

    struct shm_buffer bufs[2] = {0};

    for (int i = 0; i < 2; ++i) {
        int fd = create_shm_file(size);
        if (fd < 0) {
            perror("create_shm_file");
            return 1;
        }

        void *data = mmap(NULL, size,
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED, fd, 0);
        if (data == MAP_FAILED) {
            perror("mmap");
            close(fd);
            return 1;
        }

        struct wl_shm_pool *pool =
            wl_shm_create_pool(shm, fd, (int)size);
        struct wl_buffer *buffer =
            wl_shm_pool_create_buffer(pool, 0,
                                      width, height, stride,
                                      WL_SHM_FORMAT_ARGB8888);
        wl_shm_pool_destroy(pool);
        close(fd);

        cairo_surface_t *c_surface =
            cairo_image_surface_create_for_data(
                (unsigned char *)data,
                CAIRO_FORMAT_ARGB32,
                width, height, stride);

        bufs[i].data      = data;
        bufs[i].size      = size;
        bufs[i].c_surface = c_surface;
        bufs[i].buffer    = buffer;
        bufs[i].busy      = false;

        wl_buffer_add_listener(buffer,
                               &buffer_listener, &bufs[i]);

        /* Clear buffer initially */
        cairo_t *cr = cairo_create(c_surface);
        cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_paint(cr);
        cairo_destroy(cr);
        cairo_surface_flush(c_surface);
    }

    /* Attach first buffer so the window appears immediately */
    wl_surface_attach(surface, bufs[0].buffer, 0, 0);
    wl_surface_damage(surface, 0, 0, width, height);
    wl_surface_commit(surface);
    wl_display_flush(display);


/*---------------------------------------------------------------------------------------------*/
//    * M A I N   E V E N T   L O O P *
/*---------------------------------------------------------------------------------------------*/

    int cur = 0; /* index of buffer used for drawing */
    int wl_fd = wl_display_get_fd(display);

    printf("Starting main loop. Click and drag to move window. Press Ctrl+C to quit.\n");

    while (running) {
        /* Process already queued Wayland events */
        wl_display_dispatch_pending(display);

        /* Wait for Wayland events OR timeout (tick) */
        struct pollfd pfd = {
            .fd     = wl_fd,
            .events = POLLIN,
            .revents = 0
        };

        int poll_ret = poll(&pfd, 1, 1000); /* 1 second tick */

        if (poll_ret > 0) {
            /* Wayland events available */
            wl_display_dispatch(display);
        }
        else if (poll_ret == 0) {

/*---------------------------------------------------------------------------------------------*/
//              TICK (periodic redraw)
/*---------------------------------------------------------------------------------------------*/
            /* Wait until a free buffer is available */
            while (bufs[cur].busy && running)
                wl_display_dispatch(display);

            if (!running)
                break;

            cairo_t *cr = cairo_create(bufs[cur].c_surface);
            draw_orchestrator(cr);
/*---------------------------------------------------------------------------------------------*/

            cairo_destroy(cr);
            cairo_surface_flush(bufs[cur].c_surface);

            /* Submit buffer to compositor */
            wl_surface_attach(surface, bufs[cur].buffer, 0, 0);
            wl_surface_damage(surface, 0, 0, width, height);
            wl_surface_commit(surface);
            wl_display_flush(display);

            bufs[cur].busy = true;
            cur = (cur + 1) % 2;
        }
        else {
            perror("poll");
            break;
        }
    }

/*---------------------------------------------------------------------------------------------*/
//     * C L E A N U P *
/*---------------------------------------------------------------------------------------------*/

    /* Cleanup window moving module */
    xdg_move_cleanup();

    /* Uvolnit grafy */
    cleanup_orchestrator();


    for (int i = 0; i < 2; ++i) {
        cairo_surface_destroy(bufs[i].c_surface);
        munmap(bufs[i].data, bufs[i].size);
        wl_buffer_destroy(bufs[i].buffer);
    }

    xdg_toplevel_destroy(toplevel);
    xdg_surface_destroy(xdg_surf);
    wl_surface_destroy(surface);
    
    if (seat)
        wl_seat_destroy(seat);
    
    xdg_wm_base_destroy(xdg_wm_base);
    wl_shm_destroy(shm);
    wl_compositor_destroy(compositor);

    wl_display_disconnect(display);
    printf("Exited cleanly.\n");

    return 0;
}
