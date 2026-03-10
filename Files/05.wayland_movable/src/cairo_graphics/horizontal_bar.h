#ifndef HORIZONTAL_BAR_H
#define HORIZONTAL_BAR_H

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
horizontal_bar_t;


/*---------------------------------------------------------------------------------------------*/
/* HORIZONTAL PROGRESS BAR */
/*---------------------------------------------------------------------------------------------*/
void draw_horizontal_bar(cairo_t *cr,
                              double x, double y,        // levý horní roh
                              double width, double height, // rozměry
                              double percent,            // 0.0 - 100.0
                              const horizontal_bar_t *style);

#endif
