#include "storage_widget.h"
#include "../ui/ui_rect.h"
#include "../config/progressbars_init.h"
#include "../cairo_text/storage_text.h"

#include "../cairo_graphics/history_graph.h"
#include "../cairo_graphics/horizontal_bar.h"


void draw_storage_widget(cairo_t *cr, struct ui_context *ctx, struct rect bounds)
{
    int x = bounds.x;
    int y = bounds.y;
/*---DISK---------------------------------------*/

            struct rect home_bounds = bounds;
            struct rect root_bounds = { bounds.x, bounds.y + 50, bounds.w, bounds.h };

            draw_disk_header(cr, bounds);

            draw_disk_name(cr, ctx->disk_home, home_bounds);
            draw_disk_percent(cr, ctx->disk_home, home_bounds);
            draw_disk_total(cr, ctx->disk_home, home_bounds);
            draw_disk_used(cr, ctx->disk_home, home_bounds);
            draw_disk_free(cr, ctx->disk_home, home_bounds);

            draw_disk_name(cr, ctx->disk_root, root_bounds);
            draw_disk_percent(cr, ctx->disk_root, root_bounds);
            draw_disk_total(cr, ctx->disk_root, root_bounds);
            draw_disk_used(cr, ctx->disk_root, root_bounds);
            draw_disk_free(cr, ctx->disk_root, root_bounds);

            draw_disk_io_speed_read(cr, ctx->disk_root, bounds);   // NOVÉ
            draw_disk_io_speed_write(cr, ctx->disk_root, bounds);   // NOVÉ
            draw_disk_io_total(cr, ctx->disk_root, bounds);   // NOVÉ


            // DISK "/home" HORIZONTAL BAR - yellow
            draw_horizontal_bar(cr,
                                x + 160,
                                y + 15,
                                180,
                                5,
                                ctx->disk_home->percent,
                                &horizontal_bar_disk); // progress (yellow)

            // DISK "/" HORIZONTAL BAR - yellow
            draw_horizontal_bar(cr,
                                x + 160, y + 65,
                                180,
                                5,
                                ctx->disk_root->percent,
                                &horizontal_bar_disk); // progress (yellow)

            /* Disk read graph */
            history_graph_draw(cr, ctx->disk_read_graph,
                               x + 10, y + 140,
                               150,     // w
                                50,      // h
                                1,       // rámeček 0 = off / 1 = on
                                1,       // mřížka  0 = off / 1 = on
                                0,       // label   0 = off / 1 = on
                                1        // pozadí  0 = off / 1 = on
                               );

            /* Disk write graph */
            history_graph_draw(cr, ctx->disk_write_graph,
                               x + 320, y + 140,
                               150,     // w
                                50,      // h
                                1,       // rámeček 0 = off / 1 = on
                                1,       // mřížka  0 = off / 1 = on
                                0,       // label   0 = off / 1 = on
                                1        // pozadí  0 = off / 1 = on
                               );

}
