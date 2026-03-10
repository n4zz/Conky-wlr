#include "sys_info_static_text.h"
#include <stdio.h>

/*---------------------------------------------------------------------------------------------*/
//  SYSTEM INFORMATION STATIC ONELINE
/*---------------------------------------------------------------------------------------------*/

void draw_system_info_oneline(cairo_t *cr, struct system_info_static *info, struct rect bounds)
{
    cairo_select_font_face(cr, "Sans",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 11.0);  /* menší font pro dlouhý text */
    cairo_set_source_rgba(cr, 0.2, 0.6, 1.0, 1.0);

    char buf[512];
    /*    snprintf(buf, sizeof(buf),
     *        "%s • %s • %s@%s • %s",
     *        info->distro_name,
     *        info->kernel_version,
     *        info->username,
     *        info->hostname,
     *        info->desktop_env);*/

    snprintf(buf, sizeof(buf),
             "%s • %s • %s",
             info->distro_name,
             info->kernel_version,
             info->desktop_env);

    cairo_move_to(cr, bounds.x + 50, bounds.y + 35);
    cairo_show_text(cr, buf);
}
