#include "date_text.h"
#include "time.h"

/*---------------------------------------------------------------------------------------------*/
//  DATE TEXT
/*---------------------------------------------------------------------------------------------*/

void draw_date_text(cairo_t *cr, struct rect bounds)
{
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

    char date_str[64];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(date_str, sizeof(date_str), "%A %d %b %Y", tm_info);

     cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_font_size(cr, 15.0);

    /* Draw shadow */
    cairo_set_source_rgba(cr, 0, 0, 0, 0.6);

    cairo_move_to(cr, bounds.x + 32, bounds.y + 82);
    cairo_show_text(cr, date_str);

    /* Draw main text */
    cairo_set_source_rgb(cr, 1.0, 0.5, 0.0);

    cairo_move_to(cr, bounds.x + 30, bounds.y + 80);
    cairo_show_text(cr, date_str);
}
