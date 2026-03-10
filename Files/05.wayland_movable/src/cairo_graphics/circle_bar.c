#include "circle_bar.h"
#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>


/*---------------------------------------------------------------------------------------------*/
//*     CIRCLE PROGRESS BAR
/*---------------------------------------------------------------------------------------------*/
void draw_circular_progress_custom(cairo_t *cr,
                            double x, double y,      // střed
                            double percent,          // 0.0 - 100.0
                            const circle_bar_t *style)  // barva progress
{
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

    /* BACKGROUND */
    cairo_new_path(cr);
    cairo_arc(cr, x, y, style->radius, 0, 2 * M_PI);
    cairo_set_source_rgba(cr,
                          style->bg.r,
                          style->bg.g,
                          style->bg.b,
                          style->bg.a);
    cairo_set_line_width(cr, style->frame_line_width);
    cairo_stroke(cr);

    /* PROGRESS ARC */
    if (percent > 0.1) {
        cairo_new_path(cr);
        double angle = (percent / 100.0) * 2 * M_PI;
        cairo_arc(cr, x, y, style->radius,
                -M_PI/2,                    // začátek nahoře
                -M_PI/2 + angle);           // konec podle %
        cairo_set_source_rgb(cr,
                              style->fg.r,
                              style->fg.g,
                              style->fg.b);
        cairo_set_line_width(cr, style->frame_line_width);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);  // zaoblené konce
        cairo_stroke(cr);
    }

    /* TEXT IN MIDDLE */
    char buf[32];
    snprintf(buf, sizeof(buf), "%.0f%%", percent);
    cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
    cairo_select_font_face(cr, "Orbitron",
                          CAIRO_FONT_SLANT_NORMAL,
                          CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 11.0);

    cairo_text_extents_t extents;
    cairo_text_extents(cr, buf, &extents);
    cairo_move_to(cr,
                  x - extents.width/2,
                  y + extents.height/2);
    cairo_show_text(cr, buf);

cairo_restore(cr);
}
