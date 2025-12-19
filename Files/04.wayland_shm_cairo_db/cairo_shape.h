#ifndef CAIRO_SHAPE_H
#define CAIRO_SHAPE_H

#include <cairo/cairo.h>

/* Draw frame */
void draw_frame_main(cairo_t *cr);

void draw_frame_2nd(cairo_t *cr);

void draw_circle(cairo_t *cr, double xc, double yc, double r);

void draw_line_h(cairo_t *cr);

void draw_line_v(cairo_t *cr);

void draw_triangle(cairo_t *cr);

#endif
