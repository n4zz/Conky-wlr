#ifndef GAUGE_BAR_H
#define GAUGE_BAR_H

#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>


typedef struct {
    struct { double r, g, b, a; } frame_color;
    double line_width;

    double radius;

    struct { double r, g, b, a; } bg;
    struct { double r, g, b; } fg;

    int show_needle;          // 0/1
    double needle_width;      // tloušťka ručičky
    double needle_length;     // délka ručičky (0 = auto)
    double needle_center_size; // velikost středového kolečka
}
gauge_bar_t;

/*---------------------------------------------------------------------------------------------*/
//*     GAUGE PROGRESSBAR
/*---------------------------------------------------------------------------------------------*/

void draw_gauge_progress(cairo_t *cr,
                        double x, double y,          // střed gauge
                        double value,                // 0–100 %
                        const gauge_bar_t *style);

#endif
