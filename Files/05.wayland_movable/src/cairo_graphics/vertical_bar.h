#ifndef VERTICAL_BAR_H
#define VERTICAL_BAR_H

#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>


typedef struct {
    struct { double r, g, b, a; } frame_color;
    double frame_line_width;

    int segments;
    double gap;

    int show_frame;
    int show_label;

    struct { double r, g, b, a; } bg;
    struct { double r, g, b; } fg;
}
vertical_bar_t;


/*---------------------------------------------------------------------------------------------*/
/* VERTICAL PROGRESS BAR WITH SEGMENTS */
/*---------------------------------------------------------------------------------------------*/
void draw_vertical_bar(cairo_t *cr,
                            double x, double y,
                            double width, double height,
                            double percent,
                            const vertical_bar_t *style);

#endif
