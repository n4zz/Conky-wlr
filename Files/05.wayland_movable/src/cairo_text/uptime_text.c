#include "uptime_text.h"
#include "../utils/helper_function.h"
#include <stdio.h>

/*---------------------------------------------------------------------------------------------*/
//*     UPTIME
/*---------------------------------------------------------------------------------------------*/

/* Systémový uptime */
void draw_system_uptime(cairo_t *cr, struct rect bounds)
{
    uint64_t uptime_sec = get_system_uptime();

    uint64_t days = uptime_sec / 86400;
    uint64_t hours = (uptime_sec % 86400) / 3600;
    uint64_t minutes = (uptime_sec % 3600) / 60;

    char buf[64];
    if (days > 0) {
        snprintf(buf, sizeof(buf), "Uptime: %lud %luh %lum", days, hours, minutes);
    } else if (hours > 0) {
        snprintf(buf, sizeof(buf), "Uptime: %luh %lum", hours, minutes);
    } else {
        snprintf(buf, sizeof(buf), "Uptime: %lum", minutes);
    }

    cairo_set_font_size(cr, 10.0);
    cairo_set_source_rgb(cr, 1.0, 0.2, 0.0);

    cairo_move_to(cr, bounds.x + 365, bounds.y + 5);
    cairo_show_text(cr, buf);
}
