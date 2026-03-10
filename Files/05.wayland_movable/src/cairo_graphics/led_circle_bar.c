#include "led_circle_bar.h"
#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>

/*---------------------------------------------------------------------------------------------*/
/* Led circle progress*/
/*---------------------------------------------------------------------------------------------*/
void draw_led_circle(
    cairo_t *cr,
    double x, double y,
    double value,               // 0–100 %
    const char *unit,          // Jednotky k zobraze
    const led_circle_bar_t *style
) {

    cairo_save(cr);

    /* ---------------------------------------------------------
        FRAME (pokud je zapnutý)
    --------------------------------------------------------- */
    if (style->show_frame) {
        cairo_set_line_width(cr, style->frame_width);
        cairo_set_source_rgba(cr,
                            style->frame_color.r,
                            style->frame_color.g,
                            style->frame_color.b,
                            style->frame_color.a);

        cairo_new_path(cr);
        cairo_arc(cr, x, y, style->frame_radius, 0, 2 * M_PI);
        cairo_stroke(cr);
    }

    double full_angle = 2 * M_PI;
    double step = full_angle / style->segments;

    //int active_segments = (int)(style->segments * (value / 100.0));
    int active_segments = round(style->segments * (value / 100.0));

    cairo_set_line_width(cr, style->line_width);

    for (int i = 0; i < style->segments; i++) {
        double a1 = i * step;
        double a2 = a1 + step * style->segment_fill;

        int is_active = (i < active_segments);

         /* ---------------------------------------------------------
           Glow efekt (jen pro aktivní segmenty) on/off
        --------------------------------------------------------- */
         if (style->glow) {
            if (is_active) {
                // Glow 1 – širší, slabší
                cairo_set_line_width(cr, style->line_width * style->glow_line1);   // *3
                cairo_set_source_rgba(cr,
                                    style->on.r,
                                    style->on.g,
                                    style->on.b,
                                    0.12);
                cairo_new_path(cr);
                cairo_arc(cr, x, y, style->radius, a1, a2);
                cairo_stroke(cr);

                // Glow 2 – užší, silnější
                cairo_set_line_width(cr, style->line_width * style->glow_line2);   // *1.8
                cairo_set_source_rgba(cr,
                                    style->on.r,
                                    style->on.g,
                                    style->on.b,
                                    0.25);
                cairo_new_path(cr);
                cairo_arc(cr, x, y, style->radius, a1, a2);
                cairo_stroke(cr);
            }
         }
        /* ---------------------------------------------------------
           Hlavní segment
        --------------------------------------------------------- */
        cairo_set_line_width(cr, style->line_width);

        if (is_active)
            cairo_set_source_rgb(cr,
                                 style->on.r,
                                 style->on.g,
                                 style->on.b);
        else
            cairo_set_source_rgb(cr,
                                 style->off.r,
                                 style->off.g,
                                 style->off.b);


        cairo_new_path(cr);
        cairo_arc(cr, x, y, style->radius, a1, a2);
        cairo_stroke(cr);


    }

     /* Text uprostřed */
    if (style->show_label) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%.0f%s", value, unit);
        cairo_set_source_rgba(cr, 0.9, 0.9, 0.9, 1.0);
        //cairo_set_source_rgb(cr, on_r, on_g, on_b); // barva podle progress
        cairo_select_font_face(cr, "Orbitron",
                            CAIRO_FONT_SLANT_NORMAL,
                            CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 12.0);

        cairo_text_extents_t extents;
        cairo_text_extents(cr, buf, &extents);
        cairo_move_to(cr,
                    x - extents.width/2,
                    y + extents.height/2);
        cairo_show_text(cr, buf);
    }
    cairo_restore(cr);
}
