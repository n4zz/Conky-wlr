#include "cairo_shape.h"
#include <math.h>



/*---------------------------------------------------------------------------------------------*/
//*   RECTANGLE
/*---------------------------------------------------------------------------------------------*/
void draw_rectangle(cairo_t *cr) {

    /*výplň*/
    cairo_save(cr);
    cairo_rectangle (cr, 20, 20, 120, 80);
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.5); /* tmavé pozadí s alfa */
    cairo_fill(cr);
    cairo_restore(cr);

    /* --- Ohraničení (stroke) --- */
    cairo_save(cr);
    cairo_rectangle (cr, 20, 20, 120, 80);
    cairo_set_line_width(cr,3);
    /* barva ohraničení */
    cairo_set_source_rgba(cr, 0.2, 0.6, 1.0, 1.0);
    cairo_stroke(cr);
    cairo_restore(cr);
}
/*---------------------------------------------------------------------------------------------*/
//*    HORIZONTAL LINE
/*---------------------------------------------------------------------------------------------*/
void draw_line_h(cairo_t *cr) {

    /* Stín */
    cairo_save(cr);
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.55); /* černý stín s alfa */
    cairo_set_line_width(cr, 1.5);             /* tloušťka 1.5 px */
    cairo_move_to(cr, 92.0, 42.0);
    cairo_line_to(cr, 422.0, 42.0);
    cairo_stroke(cr);
    cairo_restore(cr);

    /* Line */
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.5);
    cairo_set_line_width(cr, 1.0);             /* tloušťka 1 px */
    cairo_move_to(cr, 90.0, 40.0);
    cairo_line_to(cr, 420.0, 40.0);
    cairo_stroke(cr);

}

/*---------------------------------------------------------------------------------------------*/
//*    VERTICAL LINE
/*---------------------------------------------------------------------------------------------*/
void draw_line_v(cairo_t *cr) {

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_set_line_width (cr, 5.0);
    cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND);
    cairo_move_to (cr, 30.0, 170.0); cairo_line_to (cr, 30.0, 250.0);
    cairo_stroke (cr);
    cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND);
    cairo_move_to (cr, 450.0, 170.0); cairo_line_to (cr, 450.0, 250.0);
    cairo_stroke (cr);

    /* draw helping lines */
    cairo_set_source_rgb (cr, 1.0, 0.3, 0.0);
    cairo_set_line_width (cr, 1.00);
    cairo_move_to (cr, 30.0, 170.0);  cairo_line_to (cr, 30.0, 250.0);
    cairo_move_to (cr, 450.0, 170.0);  cairo_line_to (cr, 450.0, 250.0);
    cairo_stroke (cr);

}

/*---------------------------------------------------------------------------------------------*/
//*     CIRCLE WITH FRAME
/*---------------------------------------------------------------------------------------------*/
void draw_circle(cairo_t *cr, double xc, double yc, double r) {
    /* nastavit barvu výplně */
    cairo_set_source_rgb(cr, 0.2, 0.6, 0.9);
    /* vytvořit kruh (0..2*PI) */
    cairo_arc(cr, xc, yc, r, 0, 2*M_PI);
    cairo_fill_preserve(cr); /* vyplní, ale ponechá cestu pro stroke */

    /* nastavit obrys */
    cairo_set_line_width(cr, 2.0);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
}

/*---------------------------------------------------------------------------------------------*/
//*     TRIANGLE
/*---------------------------------------------------------------------------------------------*/
void draw_triangle(cairo_t *cr) {
    cairo_move_to (cr, 200.0, 300.0);
    cairo_rel_line_to (cr, 30.0, -30.0);
    cairo_rel_line_to (cr, 30.0, 30.0);
    cairo_close_path (cr);

    cairo_set_line_width (cr, 1.0);
    cairo_set_source_rgb (cr, 0, 0.3, 1);
    cairo_fill_preserve (cr);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);
}
