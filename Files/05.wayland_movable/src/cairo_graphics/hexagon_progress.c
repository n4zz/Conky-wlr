#include "hexagon_progress.h"
#include <cairo/cairo.h>
#include <math.h>

/*---------------------------------------------------------------------------------------------*/
//*     HEXAGON PROGRESSBAR
/*---------------------------------------------------------------------------------------------*/

void draw_hexagon_progress(
    cairo_t *cr,
    double x, double y,        // střed hexagonu
    double value,              // 0-100%
    const hexagon_bar_t *style
) {
    cairo_save(cr);

    // Hexagon ležící na vodorovné straně (dolní strana je vodorovná)
    // 6 vrcholů ve správném pořadí (po směru hodinových ručiček od 0%)
    double hex[6][2] = {
        {x - style->size * 0.5,  y + style->size * 0.866},  // 0% - vlevo dole
        {x - style->size,        y},                  // 20% - levý vrchol (uprostřed vlevo)
        {x - style->size * 0.5,  y - style->size * 0.866},  // 40% - vlevo nahoře
        {x + style->size * 0.5,  y - style->size * 0.866},  // 60% - vpravo nahoře
        {x + style->size,        y},                  // 80% - pravý vrchol (uprostřed vpravo)
        {x + style->size * 0.5,  y + style->size * 0.866}   // 100% - vpravo dole
    };

    cairo_set_line_width(cr, style->line_width);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);

    // Pozadí - celý hexagon
    cairo_new_path(cr);
    cairo_move_to(cr, hex[0][0], hex[0][1]);
    for (int i = 1; i < 6; i++) {
        cairo_line_to(cr, hex[i][0], hex[i][1]);
    }
    cairo_close_path(cr);
    cairo_set_source_rgb(cr,
                         style->bg.r,
                         style->bg.g,
                         style->bg.b);
    cairo_stroke(cr);

    // Progress - vykreslení podle hodnoty
    if (value > 0) {
        double progress = value / 100.0;
        if (progress > 1.0) progress = 1.0;

        // Celková cesta má 5 segmentů (od vrcholu 0 k vrcholu 5)
        double total_segments = 5.0;
        double current_progress = progress * total_segments;

        cairo_new_path(cr);
        cairo_set_source_rgb(cr,
                             style->fg.r,
                             style->fg.g,
                             style->fg.b);
        cairo_move_to(cr, hex[0][0], hex[0][1]);

        int full_segments = (int)current_progress;
        double partial = current_progress - full_segments;

        // Kreslení celých segmentů
        for (int i = 0; i < full_segments && i < 5; i++) {
            cairo_line_to(cr, hex[i + 1][0], hex[i + 1][1]);
        }

        // Kreslení částečného segmentu
        if (full_segments < 5 && partial > 0) {
            double x1 = hex[full_segments][0];
            double y1 = hex[full_segments][1];
            double x2 = hex[full_segments + 1][0];
            double y2 = hex[full_segments + 1][1];

            double px = x1 + (x2 - x1) * partial;
            double py = y1 + (y2 - y1) * partial;

            cairo_line_to(cr, px, py);
        }

        cairo_stroke(cr);
    }

    cairo_restore(cr);
}

void draw_hexagon_labels(
    cairo_t *cr,
    double x, double y,        // střed hexagonu
    const labels_t *style
) {
    cairo_save(cr);

    // Stejné vrcholy jako u hexagonu
    double hex[6][2] = {
        {x - style->size * 0.5,  y + style->size * 0.866},  // 0%
        {x - style->size,        y},                  // 20%
        {x - style->size * 0.5,  y - style->size * 0.866},  // 40%
        {x + style->size * 0.5,  y - style->size * 0.866},  // 60%
        {x + style->size,        y},                  // 80%
        {x + style->size * 0.5,  y + style->size * 0.866}   // 100%
    };

    double offset = style->line_width + 10;

    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
    cairo_select_font_face(cr, "Sans",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 11);

    for (int i = 0; i < style->count; i++) {

        const char *label = style->text[i];

        // Vyber vrchol podle počtu labelů
        int vertex = (int)round(i * (6.0 / style->count));
        vertex = vertex % 6;

        double vx = hex[vertex][0];
        double vy = hex[vertex][1];

        // Offset ven
        double dx = vx - x;
        double dy = vy - y;
        double dist = sqrt(dx*dx + dy*dy);

        dx = dx / dist * offset;
        dy = dy / dist * offset;

        cairo_text_extents_t extents;
        cairo_text_extents(cr, label, &extents);

        double text_x = vx + dx - extents.width / 2;
        double text_y = vy + dy + extents.height / 2;

        cairo_move_to(cr, text_x, text_y);
        cairo_show_text(cr, label);
    }
    cairo_restore(cr);
}
