#include "gauge_bar.h"
#include <cairo/cairo.h>
#include <math.h>


/*---------------------------------------------------------------------------------------------*/
//*     GAUGE PROGRESSBAR
/*---------------------------------------------------------------------------------------------*/
void draw_gauge_progress(
    cairo_t *cr,
    double x, double y,          // střed gauge
    double value,                // 0–100 %
    const gauge_bar_t *style)
{
    cairo_save(cr);
    // Normalizace hodnoty na 0.0 - 1.0
    double progress = value / 100.0;
    if (progress < 0.0) progress = 0.0;
    if (progress > 1.0) progress = 1.0;

    // Úhly pro půlkruh (od 180° do 360°/0°)
    double start_angle = M_PI;        // 180°
    double end_angle = 2.0 * M_PI;    // 360°/0°

    // Nastavení tloustky čáry
    cairo_set_line_width(cr, style->line_width);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);

    // Pozadí gauge (šedá/pozadí)
    cairo_new_path(cr);
    cairo_set_source_rgb(cr,
                         style->bg.r,
                         style->bg.g,
                         style->bg.b);
    cairo_arc(cr, x, y, style->radius, start_angle, end_angle);
    cairo_stroke(cr);

    // Progress arc (barevný)
    if (progress > 0.0) {
        cairo_new_path(cr);
        cairo_set_source_rgb(cr,
                             style->fg.r,
                             style->fg.g,
                             style->fg.b);
        double progress_angle = start_angle + (end_angle - start_angle) * progress;
        cairo_arc(cr, x, y, style->radius, start_angle, progress_angle);
        cairo_stroke(cr);
    }

    if (style->show_needle) {
        // Ručička
        double needle_angle = start_angle + (end_angle - start_angle) * progress;
        //double needle_length = style->radius - 5;
        double needle_length = (style->needle_length > 0)
                       ? style->needle_length
                       : style->radius - 5;

        // Výpočet pozice konce ručičky
        double needle_x = x + needle_length * cos(needle_angle);
        double needle_y = y + needle_length * sin(needle_angle);

        // Nakreslení ručičky
        cairo_new_path(cr);
        cairo_set_source_rgb(cr,
                            style->fg.r,
                            style->fg.g,
                            style->fg.b);
        cairo_set_line_width(cr, style->needle_width);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        cairo_move_to(cr, x, y);
        cairo_line_to(cr, needle_x, needle_y);
        cairo_stroke(cr);

        // Střed ručičky (kolečko)
        cairo_new_path(cr);
        cairo_arc(cr, x, y, style->needle_center_size, 0, 2*M_PI);
        cairo_fill(cr);
        cairo_restore(cr);
    }
}
