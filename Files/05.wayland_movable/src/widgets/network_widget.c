#include "../ui/ui_rect.h"
#include "../ui/ui_context.h"
#include "../cairo_text/network_text.h"
#include "..//config/progressbars_init.h"


#include "../cairo_graphics/history_graph.h"
//#include "../cairo_graphics/horizontal_bar.h"
#include "../cairo_graphics/vertical_bar.h"
#include "../cairo_graphics/hexagon_progress.h"
#include "../cairo_graphics/circle_bar.h"

//#include "../cairo_graphics/gauge_marks.h"
//#include "../cairo_graphics/gauge_labels.h"
//#include "../cairo_graphics/gauge_bar.h"
//#include "../cairo_graphics/led_circle_bar.h"

void draw_network_widget(cairo_t *cr, struct ui_context *ctx, struct rect bounds)
{
            int x = bounds.x;
            int y = bounds.y;
 /*---NET----------------------------------------*/
            //draw_network_header(cr, bounds);
            draw_network_interface(cr, ctx->net, bounds); // Název rozhraní + UP/DOWN status
            draw_ip_text(cr, ctx->ip, bounds);
            draw_wifi_signal(cr, ctx->net, bounds);       // WiFi signál (jen pokud is_wifi)

            draw_network_d_speed(cr, ctx->net,bounds);   // Download Rychlost ↓
            draw_network_u_speed(cr, ctx->net,bounds);   // Upload Rychlost ↑

            draw_network_total_down(cr, ctx->net,bounds);     // Celkový přenos download ↓
            draw_network_total_up(cr, ctx->net,bounds);     // Celkový přenos upload↑


             // Wifi Signal % HORIZONTAL BAR - yellow
            /*draw_horizontal_bar(cr,
                                x + 200,
                                y + 715,
                                180,
                                5,
                                ctx->net->signal_percent,
                                &horizontal_bar_network);*/



             /* Download graph */
            history_graph_draw(cr, ctx->net_rx_graph,
                               x + 10,
                               y + 130,
                               150,     // w
                                50,      // h
                                0,       // rámeček 0 = off / 1 = on
                                1,       // mřížka  0 = off / 1 = on
                                1,       // label   0 = off / 1 = on
                                1        // pozadí  0 = off / 1 = on
                               );

            /* Upload graph*/
            history_graph_draw(cr, ctx->net_tx_graph,
                               x + 320,
                               y + 130,
                                150,     // w
                                50,      // h
                                0,       // rámeček 0 = off / 1 = on
                                1,       // mřížka  0 = off / 1 = on
                                1,       // label   0 = off / 1 = on
                                1        // pozadí  0 = off / 1 = on
                               );

            draw_vertical_bar(cr,
                              x + 350,
                              y + 20,
                              10,  // šířka
                              65, // výška
                              ctx->net->signal_percent,
                              &vertical_bar_network);

            draw_vertical_bar(cr,
                              x + 130,
                              y + 20,
                              10,  // šířka
                              65, // výška
                              ctx->net->signal_percent,
                              &vertical_bar_network);

            draw_hexagon_progress(cr,
            x + 60, y + 50,           // pozice
            ctx->net->signal_percent,
            &hexagon_bar_network);

            draw_hexagon_labels(cr,
            x + 60, y + 50,           // stejná pozice
            &labels_network);

            draw_circular_progress_custom(cr,
                                          x + 420,
                                          y + 50,
                                          ctx->net->signal_percent,
                                          &circle_bar_network);
}
