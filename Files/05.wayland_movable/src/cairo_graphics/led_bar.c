#include "led_bar.h"

#include <cairo/cairo.h>
//#include <stdio.h>
#include <math.h>

void draw_led_segment_bar(cairo_t *cr,
                          double x, double y,        // levý horní roh
                          double width, double height,
                          double percent,            // 0-100
                          const led_bar_t *style)
{
    // Výpočet velikosti jedné LED
    double total_gap = style->gap * (style->segments - 1);
    double led_width = (width - total_gap) / style->segments;
    double led_height = height;

    // Kolik LED má svítit
    int active_leds = (int)((percent / 100.0) * style->segments);

    // Vykreslit jednotlivé LED
    for (int i = 0; i < style->segments; i++) {
        double led_x = x + i * (led_width + style->gap);

        // Určit barvu (aktivní / neaktivní)
        if (i < active_leds) {
            // Zapnutá LED - jasná barva
            cairo_set_source_rgba(cr,
                                  style->fg.r,
                                  style->fg.g,
                                  style->fg.b,
                                  style->fg.a); //1
        } else {
            // Vypnutá LED - tmavá barva
            cairo_set_source_rgba(cr,
                                  style->bg.r,
                                  style->bg.g,
                                  style->bg.b,
                                  style->bg.a);//0.3
        }

        // Nakreslit kruh (LED)
        double radius = led_height / 2.0;
        cairo_arc(cr, led_x + radius, y + radius, radius, 0, 2 * M_PI);
        cairo_fill(cr);

        // GLOW efekt (pro zapnuté LED)
        if (i < active_leds) {
            cairo_pattern_t *glow = cairo_pattern_create_radial(
                led_x + radius, y + radius, 0,
                led_x + radius, y + radius, radius * 1.5
            );
            cairo_pattern_add_color_stop_rgba(glow, 0.0,
                                              style->fg.r,
                                              style->fg.g,
                                              style->fg.b,
                                              0.8); //0.8
            cairo_pattern_add_color_stop_rgba(glow, 1.0,
                                              style->fg.r,
                                              style->fg.g,
                                              style->fg.b,
                                              0.0); //0.0

            cairo_set_source(cr, glow);
            cairo_arc(cr, led_x + radius, y + radius, radius * 1.5, 0, 2 * M_PI);
            cairo_fill(cr);
            cairo_pattern_destroy(glow);
        }
    }
}
