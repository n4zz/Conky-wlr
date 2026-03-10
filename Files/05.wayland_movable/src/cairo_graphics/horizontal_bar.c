#include "horizontal_bar.h"
#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
/* HORIZONTAL SEGMENTS PROGRESS BAR */
/*---------------------------------------------------------------------------------------------*/
void draw_horizontal_bar(cairo_t *cr,
                              double x, double y,          // levý horní roh
                              double width, double height, // rozměry
                              double percent,              // 0.0 - 100.0
                              const horizontal_bar_t *style)
{
    cairo_save(cr);
    /* Jediný segment = klasický progressbar */
    if (style->segments == 1) {
        double filled_w = width * (percent / 100.0);

        /* Pozadí */
        cairo_rectangle(cr, x, y, width, height);
        cairo_set_source_rgba(cr,
                            style->bg.r,
                            style->bg.g,
                            style->bg.b,
                            style->bg.a);
        cairo_fill(cr);

        /* Progress (vyplněná část - barevná) */
        cairo_rectangle(cr, x, y, filled_w, height);
        cairo_set_source_rgb(cr,
                              style->fg.r,
                              style->fg.g,
                              style->fg.b);
        cairo_fill(cr);

        cairo_fill(cr);

        /* Rámeček */
        if (style->show_frame) {
            cairo_rectangle(cr, x, y, width, height);
            cairo_set_source_rgba(cr,
                                style->frame_color.r,
                                style->frame_color.g,
                                style->frame_color.b,
                                style->frame_color.a);
            cairo_set_line_width(cr, style->frame_line_width);
            cairo_stroke(cr);
        }

        /* Popisek (volitelně) */
        if (style->show_label) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%.0f%%", percent);

            cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
            cairo_select_font_face(cr, "Sans",
                                CAIRO_FONT_SLANT_NORMAL,
                                CAIRO_FONT_WEIGHT_BOLD);
            cairo_set_font_size(cr, 12.0);

            cairo_text_extents_t extents;
            cairo_text_extents(cr, buf, &extents);

            cairo_move_to(cr,
                        x + width/2 - extents.width/2,
                        y + height/2 + extents.height/2);

            cairo_show_text(cr, buf);
        }

        cairo_restore(cr);
        return;
    }
    /* Šířka jednoho segmentu */
    int segments = style->segments;
    double gap   = style->gap;

    if (segments < 1)
        segments = 1;

    double total_gaps = (segments - 1) * gap;
    double seg_w = (width - total_gaps) / segments;

    /* Kolik segmentů má být aktivních */
    int active_segments = (int)(segments * (percent / 100.0));

    /* Pozadí (celý bar - šedý) */
    cairo_rectangle(cr, x, y, width, height);
    cairo_set_source_rgba(cr,
                          style->bg.r,
                          style->bg.g,
                          style->bg.b,
                          style->bg.a);
    cairo_fill(cr);

    /* Segmenty (zleva doprava) */
    for (int i = 0; i < segments; i++)
    {
        double seg_x = x + i * (seg_w + gap);

        if (i < active_segments)
            cairo_set_source_rgb(cr,
                                 style->fg.r,
                                 style->fg.g,
                                 style->fg.b);
        else
            cairo_set_source_rgb(cr,
                                 style->bg.r,
                                 style->bg.g,
                                 style->bg.b);

        cairo_rectangle(cr, seg_x, y, seg_w, height);
        cairo_fill(cr);
    }

    /* Rámeček (volitelně) */
    if (style->show_frame) {
        cairo_rectangle(cr, x, y, width, height);
        cairo_set_source_rgba(cr,
                              style->frame_color.r,
                              style->frame_color.g,
                              style->frame_color.b,
                              style->frame_color.a);
        cairo_set_line_width(cr, style->frame_line_width);
        cairo_stroke(cr);
    }

    /* Popisek (volitelně) */
    if (style->show_label) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%.0f%%", percent);

        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        cairo_select_font_face(cr, "Sans",
                               CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 12.0);

        cairo_text_extents_t extents;
        cairo_text_extents(cr, buf, &extents);

        cairo_move_to(cr,
                      x + width/2 - extents.width/2,
                      y + height/2 + extents.height/2);

        cairo_show_text(cr, buf);
    }

      cairo_restore(cr);
}
