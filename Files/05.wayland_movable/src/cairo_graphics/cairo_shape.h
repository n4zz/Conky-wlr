#ifndef CAIRO_SHAPE_H
#define CAIRO_SHAPE_H

#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
//*     DRAW SHAPES
/*---------------------------------------------------------------------------------------------*/

void draw_rectangle(cairo_t *cr);

void draw_circle(cairo_t *cr, double xc, double yc, double r);

void draw_line_h(cairo_t *cr);

void draw_line_v(cairo_t *cr);

void draw_triangle(cairo_t *cr);

#endif
