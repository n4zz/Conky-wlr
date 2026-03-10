#ifndef CIRCLE_BAR_H
#define CIRCLE_BAR_H

#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>


typedef struct {
    struct { double r, g, b, a; } frame_color;
    int show_frame;
    double frame_width;
    double frame_radius;
    double frame_line_width;

    double radius;

    struct { double r, g, b, a; } bg;
    struct { double r, g, b; } fg;
}
circle_bar_t;

/*---------------------------------------------------------------------------------------------*/
//*     CIRCULATER PROGRESS BAR
/*---------------------------------------------------------------------------------------------*/

/* Vykreslí kruhový progress bar
 * x, y     - střed kruhu
 * radius   - poloměr
 * percent  - hodnota 0.0 - 100.0
 */

void draw_circular_progress_custom(cairo_t *cr,
                            double x, double y,
                            double percent,
                            const circle_bar_t *style);

#endif
