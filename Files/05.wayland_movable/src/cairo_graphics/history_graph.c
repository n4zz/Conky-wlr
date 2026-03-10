/* ==========================================
 * history_graph.c - Generic History Graph Implementation
 * ========================================== */

#include "history_graph.h"
#include <stdlib.h>
#include <string.h>


void history_graph_init(struct history_graph *graph,
                        int capacity,
                        double min_value,
                        double max_value,
                        const char *label
                        )
{
    graph->capacity = capacity;
    graph->count = 0;
    graph->head = 0;
    graph->min_value = min_value;
    graph->max_value = max_value;
    graph->history = calloc(capacity, sizeof(double));

    /* Zkopírovat label (pokud není NULL) */
    if (label) {
        graph->label = strdup(label);
    } else {
        graph->label = NULL;
    }

}

void history_graph_push(struct history_graph *graph, double value)
{
    /* Ošetření rozsahu */
    if (value < graph->min_value) value = graph->min_value;
    if (value > graph->max_value) value = graph->max_value;

    /* Kruhový buffer - přepíšeme nejstarší hodnotu */
    graph->head = (graph->head + 1) % graph->capacity;
    graph->history[graph->head] = value;

    if (graph->count < graph->capacity)
        graph->count++;
}

void history_graph_set_line_color(struct history_graph *graph,
                                   double r, double g, double b, double a)
{
    graph->line_color.r = r;
    graph->line_color.g = g;
    graph->line_color.b = b;
    graph->line_color.a = a;
}

void history_graph_set_fill_gradient(struct history_graph *graph,
                                      double top_r, double top_g, double top_b, double top_a,
                                      double bot_r, double bot_g, double bot_b, double bot_a)
{
    graph->fill_gradient.top_r = top_r;
    graph->fill_gradient.top_g = top_g;
    graph->fill_gradient.top_b = top_b;
    graph->fill_gradient.top_a = top_a;

    graph->fill_gradient.bot_r = bot_r;
    graph->fill_gradient.bot_g = bot_g;
    graph->fill_gradient.bot_b = bot_b;
    graph->fill_gradient.bot_a = bot_a;
}

void history_graph_draw(cairo_t *cr,
                        struct history_graph *graph,
                        double x, double y,
                        double width, double height,
                        int show_frame,
                        int show_grid,
                        int show_label,
                        int show_background
                        )
{
    if (graph->count == 0)
        return;

    cairo_save(cr);

    /* -------------------------
     * Pozadí grafu
     * ------------------------- */
    if (show_background) {
        cairo_rectangle(cr, x, y, width, height);
        cairo_set_source_rgba(cr,
                            graph->fill_bg.r,
                            graph->fill_bg.g,
                            graph->fill_bg.b,
                            graph->fill_bg.a
        );
        cairo_fill(cr);
    }

    /* -------------------------
     * Mřížka (volitelně)
     * ------------------------- */
    if (show_grid) {
        cairo_set_source_rgba(cr,
                            graph->grid_color.r,
                            graph->grid_color.g,
                            graph->grid_color.b,
                            graph->grid_color.a
        );
        cairo_set_line_width(cr, graph->grid_line_width);

        /* Horizontální čáry (0%, 25%, 50%, 75%, 100%) */
        for (int i = 0; i <= 4; i++) {
            double grid_y = y + height - (height * i / 4.0);
            cairo_move_to(cr, x, grid_y);
            cairo_line_to(cr, x + width, grid_y);
        }
        cairo_stroke(cr);
    }

    /* -------------------------
     * Rámeček volitelně
     * ------------------------- */
    if (show_frame) {
    cairo_rectangle(cr, x, y, width, height);
    cairo_set_source_rgba(cr,
                          graph->frame_color.r,
                          graph->frame_color.g,
                          graph->frame_color.b,
                          graph->frame_color.a
    );
    cairo_set_line_width(cr, graph->frame_line_width);
    cairo_stroke(cr);
    }
    /* -------------------------
     * Kreslení grafu
     * ------------------------- */

    /* Vypočítat šířku jednoho vzorku */
    double sample_width = width / (double)(graph->capacity - 1);

    /* Rozsah hodnot */
    double value_range = graph->max_value - graph->min_value;
    if (value_range == 0.0) value_range = 1.0; /* ochrana před dělením nulou */

    /* Začít cestou */
    cairo_new_path(cr);

    int samples_to_draw = graph->count;
    int start_index = (graph->head - samples_to_draw + 1 + graph->capacity)
                      % graph->capacity;

    for (int i = 0; i < samples_to_draw; i++) {
        int idx = (start_index + i) % graph->capacity;
        double value = graph->history[idx];

        /* Normalizovat hodnotu do rozsahu 0.0 - 1.0 */
        double normalized = (value - graph->min_value) / value_range;

        /* Převést na Y souřadnici (invertováno - max nahoře) */
        double sample_y = y + height - (normalized * height);
        double sample_x = x + (i * sample_width);

        if (i == 0)
            cairo_move_to(cr, sample_x, sample_y);
        else
            cairo_line_to(cr, sample_x, sample_y);
    }

    /* Vyplnění pod křivkou (gradient) */
    if (samples_to_draw > 0) {
        /* Dokončit cestu k dolnímu okraji pro výplň */
        double last_x = x + ((samples_to_draw - 1) * sample_width);
        cairo_line_to(cr, last_x, y + height);
        cairo_line_to(cr, x, y + height);
        cairo_close_path(cr);

        /* Gradient výplň */
        cairo_pattern_t *gradient =
            cairo_pattern_create_linear(0, y, 0, y + height);

        cairo_pattern_add_color_stop_rgba(gradient, 0.0,
            graph->fill_gradient.top_r,
            graph->fill_gradient.top_g,
            graph->fill_gradient.top_b,
            graph->fill_gradient.top_a);

        cairo_pattern_add_color_stop_rgba(gradient, 1.0,
            graph->fill_gradient.bot_r,
            graph->fill_gradient.bot_g,
            graph->fill_gradient.bot_b,
            graph->fill_gradient.bot_a);

        cairo_set_source(cr, gradient);
        cairo_fill_preserve(cr);
        cairo_pattern_destroy(gradient);
    }

    /* Překreslit obrys křivky */
    cairo_new_path(cr);
    start_index = (graph->head - samples_to_draw + 1 + graph->capacity)
                  % graph->capacity;

    for (int i = 0; i < samples_to_draw; i++) {
        int idx = (start_index + i) % graph->capacity;
        double value = graph->history[idx];
        double normalized = (value - graph->min_value) / value_range;
        double sample_y = y + height - (normalized * height);
        double sample_x = x + (i * sample_width);

        if (i == 0)
            cairo_move_to(cr, sample_x, sample_y);
        else
            cairo_line_to(cr, sample_x, sample_y);
    }

    cairo_set_source_rgba(cr,
        graph->line_color.r,
        graph->line_color.g,
        graph->line_color.b,
        graph->line_color.a);
    cairo_set_line_width(cr, 1.5);
    cairo_stroke(cr);

    /* -------------------------
     * Popisek (volitelně)
     * ------------------------- */
    if (show_label && graph->label) {
        cairo_select_font_face(cr, "Orbitron",
                              CAIRO_FONT_SLANT_NORMAL,
                              CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 10.0);

        /* Měření textu pro umístění */
        cairo_text_extents_t extents;
        cairo_text_extents(cr, graph->label, &extents);

        /* Umístit v levém horním rohu grafu */
        double label_x = x + 5;
        double label_y = y + 12;

        /* Stín pro lepší čitelnost */
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.7);
        cairo_move_to(cr, label_x + 1, label_y + 1);
        cairo_show_text(cr, graph->label);

        /* Samotný text */
        cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
        cairo_move_to(cr, label_x, label_y);
        cairo_show_text(cr, graph->label);
    }

    cairo_restore(cr);
}

void history_graph_destroy(struct history_graph *graph)
{
    if (graph->history) {
        free(graph->history);
        graph->history = NULL;
    }

    if (graph->label) {
        free(graph->label);
        graph->label = NULL;
    }

    graph->count = 0;
    graph->capacity = 0;
}
