#include "gpu_widget.h"
#include "../ui/ui_rect.h"
#include "../cairo_text/gpu_text.h"
#include "..//config/progressbars_init.h"

//#include "../cairo_graphics/gauge_marks.h"
//#include "../cairo_graphics/gauge_labels.h"

#include "../cairo_graphics/gauge_bar.h"
#include "../cairo_graphics/led_circle_bar.h"
#include "../cairo_graphics/vertical_bar.h"

#include "../cairo_graphics/history_graph.h"


void draw_gpu_widget(cairo_t *cr, struct ui_context *ctx, struct rect bounds)
{
            int x = bounds.x;
            int y = bounds.y;
/*---GPU----------------------------------------*/
            if (ctx->gpu->available) {
                draw_gpu_header(cr, bounds);
                draw_gpu_usage(cr, ctx->gpu->utilization_percent, bounds);
                //draw_gpu_temperature(cr, ctx->gpu.temperature_celsius);
                draw_gpu_memory_usage(cr, ctx->gpu->memory_used_percent, bounds);
                draw_gpu_frequency_core(cr, ctx->gpu->core_clock_mhz, bounds);
                draw_gpu_frequency_mem(cr, ctx->gpu->mem_clock_mhz, bounds);
                draw_gpu_power(cr, ctx->gpu->power_watt, bounds);
            }


            /* GPU USE*/

            draw_gauge_progress(
                cr,
                x + 60, y + 50,         // střed
                ctx->gpu->utilization_percent,       // hodnota 0–100 %
                &gauge_bar_gpu);

           /* GPU TEMP*/
           draw_led_circle(
                cr,
                x + 240, y + 50,       // střed
                ctx->gpu->temperature_celsius, "°C",      // hodnota
                &led_circle_bar_gpu);

           // GPU VERTICAL BAR - blue
            draw_vertical_bar(cr,
                              x + 135,
                              y + 25,
                              35,
                              50,
                              ctx->gpu->utilization_percent,
                              &vertical_bar_gpu); // style


              /* GPU graf */
            history_graph_draw(cr, ctx->gpu_graph,
                               x + 320,
                               y + 25,
                               150,     // w
                                50,      // h
                                0,       // rámeček 0 = off / 1 = on
                                0,       // mřížka  0 = off / 1 = on
                                1,       // label   0 = off / 1 = on
                                0        // pozadí  0 = off / 1 = on
                               );

}
