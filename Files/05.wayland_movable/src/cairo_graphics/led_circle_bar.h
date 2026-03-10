#ifndef LED_CIRCLE_BAR_H
#define LED_CIRCLE_BAR_H

#include <cairo/cairo.h>


typedef struct {
    struct { double r, g, b, a; } frame_color;
    int show_frame;
    double frame_width;
    double frame_radius;

    double line_width;

    double radius;

    int segments;
    double segment_fill;

    int glow;
    double glow_line1;
    double glow_line2;

    int show_label;

    struct { double r, g, b, a; } off;
    struct { double r, g, b; } on;

}
led_circle_bar_t;
/*---------------------------------------------------------------------------------------------*/
/* Led circle progress*/
/*---------------------------------------------------------------------------------------------*/
void draw_led_circle(
    cairo_t *cr,
    double x, double y,
    double value,               // 0–100 %
    const char *unit,
    const led_circle_bar_t *style);

#endif
