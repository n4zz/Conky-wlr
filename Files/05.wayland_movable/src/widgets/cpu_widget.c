#include "cpu_widget.h"
#include "../ui/ui_rect.h"

#include "../cairo_text/cpu_text.h"
#include "../cairo_graphics/arc_marks.h"
#include "../cairo_graphics/arc_labels.h"
#include "../cairo_graphics/gauge_bar.h"
#include "../cairo_graphics/led_circle_bar.h"
#include "../cairo_graphics/history_graph.h"

#include "../config/progressbars_init.h"

/* debug frame for real size widget */
//#include "../utils/helper_frame_position.h"

void draw_cpu_widget(cairo_t *cr, struct ui_context *ctx, struct rect bounds)
{
    int x = bounds.x;
    int y = bounds.y;

    /*--- CPU TEXT ---*/
    draw_cpu_header(cr, bounds);
    draw_cpu_usage(cr, ctx->cpu->usage, bounds);
    draw_cpu_frequency(cr, ctx->cpu->freq_mhz, bounds);
    //draw_cpu_temperature(cr, ctx->cpu->temp_celsius);

    /*--- CPU GAUGE ---*/
    //draw_arc_marks(cr, x + 60, y + 50, 30, 2, 5);
    draw_arc_marks(
            cr,
            x + 60, y + 50,
            30,               // radius
            2,                // line width
            3,                // line lenght
            5,                // offset
            5,                // num marks
            M_PI, 2*M_PI,     // půlkruh (gauge) = M_PI, 2*M_PI,  // kruh (circle) = 0, 2*M_PI
            0.6, 0.6, 0.6     // barva
    );


    draw_arc_labels(
            cr,
            x + 62, y + 55,   // střed
            28,               // radius
            12,               // font_size
            20,               // offset od oblouku
            3,                // num_labels
            M_PI, 2*M_PI,     // půlkruh (gauge) = M_PI, 2*M_PI,  // kruh (circle) = 0, 2*M_PI
            0.8, 0.8, 0.8     // barva textu (šedá)
    );

    draw_gauge_progress(
        cr,
        x + 60,
        y + 50,
        ctx->cpu->usage,
        &gauge_bar_cpu
    );

    /*--- CPU TEMP LED CIRCLE ---*/
    draw_led_circle(
        cr,
        x + 240, y + 50,
        ctx->cpu->temp_celsius, "°C",
        &led_circle_bar_cpu);

    /*--- CPU GRAPH ---*/
    history_graph_draw(
        cr,
        ctx->cpu_graph,
        x + 320,
        y + 25,
        150,     // w
        50,      // h
        1,       // rámeček 0 = off / 1 = on
        0,       // mřížka  0 = off / 1 = on
        1,       // label   0 = off / 1 = on
        1        // pozadí  0 = off / 1 = on
    );

    //helper_frame_position(cr, bounds);   // debug frame for real widget size
}

