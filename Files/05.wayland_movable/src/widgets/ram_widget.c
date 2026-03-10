#include "ram_widget.h"
#include "../ui/ui_rect.h"
#include "../config/progressbars_init.h"

#include "../cairo_graphics/horizontal_bar.h"
#include "../cairo_text/ram_text.h"




void draw_ram_widget(cairo_t *cr, struct ui_context *ctx, struct rect bounds)
{
        int x = bounds.x;
        int y = bounds.y;
    /*---RAM TEXT----------------------------------------*/
            draw_ram_header(cr, bounds);
            draw_ram_total(cr, ctx->ram,bounds);
            draw_ram_used(cr, ctx->ram,bounds);
            draw_ram_percent(cr, ctx->ram,bounds);

    /*---RAM HORIZONTAL SEGMENTS BAR -----------------------------*/
            draw_horizontal_bar(cr,
                                x + 160,
                                y + 12,
                                180,                  // šířka
                                5,                    // výška
                                ctx->ram->percent,    // hodnota
                                &horizontal_bar_ram);       // theme

}
