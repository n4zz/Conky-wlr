#include "main_window.h"
#include "../config/config_types.h"
#include <math.h>

extern struct app_config g_config;

/*---------------------------------------------------------------------------------------------*/
//     START MAIN WINDOW & FRAME FOR WIDGETS (rounded corners, and shadow)
/*---------------------------------------------------------------------------------------------*/

/* Pomocná funkce: vytvoří cestu zaobleného obdélníku */
static void rounded_rectangle(cairo_t *cr, double x, double y, double width, double height, double radius) {
    double r = radius;
    if (r <= 0.0) {
        cairo_rectangle(cr, x, y, width, height);
        return;
    }
    double x0 = x;
    double x1 = x + width;
    double y0 = y;
    double y1 = y + height;

    cairo_new_sub_path(cr);
    cairo_arc(cr, x1 - r, y0 + r, r, -M_PI/2.0, 0.0);
    cairo_arc(cr, x1 - r, y1 - r, r, 0.0, M_PI/2.0);
    cairo_arc(cr, x0 + r, y1 - r, r, M_PI/2.0, M_PI);
    cairo_arc(cr, x0 + r, y0 + r, r, M_PI, 3.0*M_PI/2.0);
    cairo_close_path(cr);
}

/* Hlavní funkce: vykreslí rámeček s jemným stínem a ohraničením */
void draw_frame_main(cairo_t *cr)
{
    /* POUŽIJ CONFIG místo hardcoded hodnot */
    const double x = g_config.main_window.x;
    const double y = g_config.main_window.y;
    const double width = g_config.main_window.width;
    const double height = g_config.main_window.height;
    const double radius = g_config.main_window.corner_radius;
    const double shadow_offset = g_config.main_window.shadow_offset;
    const double shadow_blur = g_config.main_window.shadow_blur;
    const double stroke_width = g_config.main_window.stroke_width;

    /* --- Stín okna (FILL) --- */
    cairo_save(cr);
    cairo_set_source_rgba(cr,
        g_config.main_window.shadow_fill.color.r,
        g_config.main_window.shadow_fill.color.g,
        g_config.main_window.shadow_fill.color.b,
        g_config.main_window.shadow_fill.alpha);
    rounded_rectangle(cr,
        x + g_config.main_window.shadow_fill.offset,
        y + g_config.main_window.shadow_fill.offset + g_config.main_window.shadow_fill.blur,
        width, height, radius);
    cairo_fill(cr);
    cairo_restore(cr);

    /* --- Stín rámečku (STROKE) --- */
    cairo_save(cr);
    cairo_set_source_rgba(cr,
        g_config.main_window.shadow_stroke.color.r,
        g_config.main_window.shadow_stroke.color.g,
        g_config.main_window.shadow_stroke.color.b,
        g_config.main_window.shadow_stroke.alpha);
    rounded_rectangle(cr,
        x + g_config.main_window.shadow_stroke.offset,
        y + g_config.main_window.shadow_stroke.offset + g_config.main_window.shadow_stroke.blur,
        width, height, radius);
    cairo_stroke(cr);
    cairo_restore(cr);

    /* --- Výplň pozadí --- */
    cairo_save(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_source_rgba(cr,
        g_config.main_window.bg_color.r,
        g_config.main_window.bg_color.g,
        g_config.main_window.bg_color.b,
        g_config.main_window.bg_color.a);
    rounded_rectangle(cr, x, y, width, height, radius);
    cairo_fill(cr);
    cairo_restore(cr);

    /* --- Ohraničení --- */
    cairo_save(cr);
    cairo_set_line_width(cr, stroke_width);
    cairo_set_source_rgba(cr,
        g_config.main_window.stroke_color.r,
        g_config.main_window.stroke_color.g,
        g_config.main_window.stroke_color.b,
        g_config.main_window.stroke_color.a);
    rounded_rectangle(cr, x + stroke_width/2.0, y + stroke_width/2.0,
                      width - stroke_width, height - stroke_width, radius);
    cairo_stroke(cr);
    cairo_restore(cr);
}
/*---------------------------------------------------------------------------------------------*/
//     END MAIN WINDOW & FRAME
/*---------------------------------------------------------------------------------------------*/
