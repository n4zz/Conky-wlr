#include "main_text.h"

//*---------------------------------------------------------------------------------------------*/
//  MAIN TEXT
/*---------------------------------------------------------------------------------------------*/

void draw_main_text(cairo_t *cr,struct rect bounds)
{
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20.0);

    /* Draw shadow text */
    cairo_set_source_rgba(cr, 0, 0, 0, 0.6);

    cairo_move_to(cr, bounds.x + 157 , bounds.y + 12 );
    cairo_show_text(cr, "Hello Wayland!");

    /* Draw main text */
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);

    cairo_move_to(cr, bounds.x + 155, bounds.y + 10);
    cairo_show_text(cr, "Hello Wayland!");

    /* Color test */
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 11.0);


}
