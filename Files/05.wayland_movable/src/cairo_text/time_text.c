
#include "time_text.h"
#include "time.h"


/*---------------------------------------------------------------------------------------------*/
//  CURRENT TIME
/*---------------------------------------------------------------------------------------------*/
void draw_current_time(cairo_t *cr, struct rect bounds)
{
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

    char time_str[16];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(time_str, sizeof(time_str), "%H : %M : %S", tm_info);

    cairo_select_font_face(cr, "Orbitron",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_font_size(cr, 25.0);

    /* Draw shadow */
    cairo_set_source_rgba(cr, 0.2, 1.0, 0.2, 0.4);

    cairo_move_to(cr, bounds.x + 302, bounds.y + 82);
    cairo_show_text(cr, time_str);

    /* Draw main text */
    cairo_set_font_size(cr, 25.0);
    cairo_set_source_rgb(cr, 0.2, 1.0, 0.2);

    cairo_move_to(cr, bounds.x + 300, bounds.y + 80);
    cairo_show_text(cr, time_str);
}
