/*
 * xdg_move.h
 * -------------------------------------------
 * Header file for interactive window moving via pointer input
 * 
 * Provides initialization and cleanup for pointer/seat handling
 * that enables dragging windows with left mouse button.
 */

#ifndef XDG_MOVE_H
#define XDG_MOVE_H

#include <wayland-client.h>
#include "xdg-shell.h"

/*
 * Initialize pointer input handling for window moving.
 * 
 * Parameters:
 *   seat     - wl_seat object from Wayland registry
 *   toplevel - xdg_toplevel that will be moved
 * 
 * Returns:
 *   0 on success, -1 on failure
 */
int xdg_move_init(struct wl_seat *seat, struct xdg_toplevel *toplevel);

/*
 * Cleanup pointer input resources.
 * Should be called before destroying seat.
 */
void xdg_move_cleanup(void);

/*
 * Get pointer object (for external cleanup if needed).
 * 
 * Returns:
 *   wl_pointer object or NULL if not initialized
 */
struct wl_pointer* xdg_move_get_pointer(void);

#endif /* XDG_MOVE_H */
