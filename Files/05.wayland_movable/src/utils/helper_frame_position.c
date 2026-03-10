#include "helper_frame_position.h"
#include <cairo/cairo.h>

/* ----- D E B U G - F R A M E -----*/

void helper_frame_position(cairo_t *cr, struct rect bounds)
{
    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.8, 0.0, 0.0); // červená
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, bounds.x, bounds.y, bounds.w, bounds.h);

    // horizontální střed
    cairo_move_to(cr, bounds.x, bounds.y + bounds.h/2);
    cairo_line_to(cr, bounds.x + bounds.w, bounds.y + bounds.h/2);

    // vertikální střed
    cairo_move_to(cr, bounds.x + bounds.w/2, bounds.y);
    cairo_line_to(cr, bounds.x + bounds.w/2, bounds.y + bounds.h);
    cairo_stroke(cr);
    cairo_restore(cr);
}
