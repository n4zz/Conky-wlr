#ifndef LED_BAR_H
#define LED_BAR_H

#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>


typedef struct {
    struct { double r, g, b, a; } frame_color;
    int show_frame;

    int segments;// počet LED
    double gap; // mezera mezi LED

    struct { double r, g, b, a; } bg;
    struct { double r, g, b, a; } fg;
}
led_bar_t;

/*---------------------------------------------------------------------------------------------*/
//*     LED PROGRESS BAR
/*---------------------------------------------------------------------------------------------*/

void draw_led_segment_bar(cairo_t *cr,
                            double x, double y,
                            double width, double height,
                            double percent,
                            const led_bar_t *style);

#endif
