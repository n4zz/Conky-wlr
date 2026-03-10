#include "sys_info_widget.h"
#include "../ui/ui_rect.h"
#include "../cairo_text/sys_info_static_text.h"
#include "../cairo_text/main_text.h"
#include "../cairo_text/date_text.h"
#include "../cairo_text/time_text.h"
#include "../cairo_text/uptime_text.h"

void draw_sys_info_widget(cairo_t *cr, struct ui_context *ctx, struct rect bounds)
{
    //int x = bounds.x;
    //int y = bounds.y;
/* Vykreslit statické informace (NOVÉ)*/
            draw_system_info_oneline(cr, ctx->sys_info, bounds);

            /* draw Text information */
            draw_date_text(cr, bounds);
            draw_main_text(cr, bounds);
            draw_current_time(cr, bounds);
            draw_system_uptime(cr, bounds);

}
