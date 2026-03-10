/*
 * xdg_move.c
 * -------------------------------------------
 * Implementation of interactive window moving via pointer input
 * 
 * Handles wl_seat capabilities, pointer events (enter, leave, motion, button, axis),
 * and initiates xdg_toplevel_move() when left mouse button is pressed.
 */

#include "xdg_move.h"
#include <stdio.h>
#include <stdint.h>
#include <linux/input-event-codes.h>

/*---------------------------------------------------------------------------------------------*/
// Module-local state
/*---------------------------------------------------------------------------------------------*/

/* Pointer and seat references */
static struct wl_pointer *m_pointer = NULL;
static struct wl_seat *m_seat = NULL;
static struct xdg_toplevel *m_toplevel = NULL;

/*---------------------------------------------------------------------------------------------*/
// Pointer event handlers
/*---------------------------------------------------------------------------------------------*/

static void pointer_enter(void *data, struct wl_pointer *wl_pointer,
                         uint32_t serial, struct wl_surface *surface,
                         wl_fixed_t sx, wl_fixed_t sy)
{
    (void)data;
    (void)wl_pointer;
    (void)serial;
    (void)surface;
    (void)sx;
    (void)sy;
    /* Mouse entered the window */
}

static void pointer_leave(void *data, struct wl_pointer *wl_pointer,
                         uint32_t serial, struct wl_surface *surface)
{
    (void)data;
    (void)wl_pointer;
    (void)serial;
    (void)surface;
    /* Mouse left the window */
}

static void pointer_motion(void *data, struct wl_pointer *wl_pointer,
                          uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    (void)data;
    (void)wl_pointer;
    (void)time;
    (void)sx;
    (void)sy;
    /* Mouse moved within the window */
}

static void pointer_button(void *data, struct wl_pointer *wl_pointer,
                          uint32_t serial, uint32_t time,
                          uint32_t button, uint32_t state)
{
    (void)data;
    (void)wl_pointer;
    (void)time;
    
    /* Left mouse button pressed - initiate interactive move */
    if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED) {
        if (m_toplevel && m_seat) {
            printf("xdg_move: Initiating window move...\n");
            xdg_toplevel_move(m_toplevel, m_seat, serial);
        }
    }
}

static void pointer_axis(void *data, struct wl_pointer *wl_pointer,
                        uint32_t time, uint32_t axis, wl_fixed_t value)
{
    (void)data;
    (void)wl_pointer;
    (void)time;
    (void)axis;
    (void)value;
    /* Mouse wheel scrolling */
}

static const struct wl_pointer_listener pointer_listener = {
    .enter = pointer_enter,
    .leave = pointer_leave,
    .motion = pointer_motion,
    .button = pointer_button,
    .axis = pointer_axis
};

/*---------------------------------------------------------------------------------------------*/
// Seat capabilities handler
/*---------------------------------------------------------------------------------------------*/

static void seat_capabilities(void *data,
                              struct wl_seat *seat,
                              uint32_t caps)
{
    (void)data;
    
    /* Check if seat has pointer (mouse) capability */
    if (caps & WL_SEAT_CAPABILITY_POINTER) {
        if (!m_pointer) {
            m_pointer = wl_seat_get_pointer(seat);
            wl_pointer_add_listener(m_pointer, &pointer_listener, NULL);
            printf("xdg_move: Pointer capability detected.\n");
        }
    } else {
        if (m_pointer) {
            wl_pointer_destroy(m_pointer);
            m_pointer = NULL;
        }
    }
}

static void seat_name(void *data, struct wl_seat *seat, const char *name)
{
    (void)data;
    (void)seat;
    printf("xdg_move: Seat name: %s\n", name);
}

static const struct wl_seat_listener seat_listener = {
    .capabilities = seat_capabilities,
    .name = seat_name
};

/*---------------------------------------------------------------------------------------------*/
// Public API implementation
/*---------------------------------------------------------------------------------------------*/

int xdg_move_init(struct wl_seat *seat, struct xdg_toplevel *toplevel)
{
    if (!seat || !toplevel) {
        fprintf(stderr, "xdg_move: Invalid parameters (seat=%p, toplevel=%p)\n",
                (void*)seat, (void*)toplevel);
        return -1;
    }
    
    m_seat = seat;
    m_toplevel = toplevel;
    
    /* Add seat listener to monitor capabilities */
    wl_seat_add_listener(m_seat, &seat_listener, NULL);
    
    printf("xdg_move: Initialized (waiting for pointer capability)\n");
    return 0;
}

void xdg_move_cleanup(void)
{
    if (m_pointer) {
        wl_pointer_destroy(m_pointer);
        m_pointer = NULL;
    }
    
    m_seat = NULL;
    m_toplevel = NULL;
    
    printf("xdg_move: Cleaned up\n");
}

struct wl_pointer* xdg_move_get_pointer(void)
{
    return m_pointer;
}
