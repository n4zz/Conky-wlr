#include "arc_marks.h"
#include <cairo/cairo.h>
#include <math.h>

/*---------------------------------------------------------------------------------------------*/
// GAUGE MARKS/*---------------------------------------------------------------------------------------------*/


void draw_arc_marks(
    cairo_t *cr,
    double x, double y,          // střed
    double radius,               // poloměr
    double line_width,           // tloušťka čáry značky
    double mark_lenght,          // délka značky
    double offset,               // vzdálenost od oblouku
    int num_marks,               // počet značek
    double start_angle,          // začátek oblouku
    double end_angle,            // konec oblouku
    double r, double g, double b // barva značek
    )
{
    if (num_marks <= 0)
        return;

    cairo_save(cr);

    cairo_set_line_width(cr, line_width);
    cairo_set_source_rgb(cr, r, g, b);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);

    for (int i = 0; i < num_marks; i++) {

        double t = (double)i / (num_marks - 1);
        double angle = start_angle + (end_angle - start_angle) * t;

        // pozice vnějšího bodu
        double outer_radius = radius + offset;
        double x_outer = x + outer_radius * cos(angle);
        double y_outer = y + outer_radius * sin(angle);

        // pozice vnitřního bodu
        double inner_radius = radius + offset - mark_lenght; // délka značky
        double x_inner = x + inner_radius * cos(angle);
        double y_inner = y + inner_radius * sin(angle);

        cairo_new_path(cr);
        cairo_move_to(cr, x_outer, y_outer);
        cairo_line_to(cr, x_inner, y_inner);
        cairo_stroke(cr);
    }

    cairo_restore(cr);
}
