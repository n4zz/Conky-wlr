#include "cairo_shape.h"
#include <math.h>

/* -------------------- FRAME -------------------- */

/* Pomocná funkce: vytvoří cestu zaobleného obdélníku */
static void rounded_rectangle(cairo_t *cr, double x, double y, double width, double height, double radius) {
    double r = radius;
    if (r <= 0.0) {
        cairo_rectangle(cr, x, y, width, height);
        return;
    }
    double x0 = x;
    double x1 = x + width;
    double y0 = y;
    double y1 = y + height;

    cairo_new_sub_path(cr);
    cairo_arc(cr, x1 - r, y0 + r, r, -M_PI/2.0, 0.0);
    cairo_arc(cr, x1 - r, y1 - r, r, 0.0, M_PI/2.0);
    cairo_arc(cr, x0 + r, y1 - r, r, M_PI/2.0, M_PI);
    cairo_arc(cr, x0 + r, y0 + r, r, M_PI, 3.0*M_PI/2.0);
    cairo_close_path(cr);
}

/* Hlavní funkce: vykreslí rámeček s jemným stínem a ohraničením */
void draw_frame_main(cairo_t *cr)
{
    /* Parametry rámečku - uprav podle potřeby */
    const double x = 10.0;
    const double y = 5.0;
    const double width = 460.0;
    const double height = 300.0;
    const double radius = 10.0;
    const double shadow_offset = 0.5;
    const double shadow_blur = 0.0; /* jednoduchý posun stínu bez rozmazání */
    const double stroke_width = 1.0;

    /* --- Stín (jednoduchý posun + průhledná černá) --- */
    cairo_save(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.35); /* černý stín s alfa */
    rounded_rectangle(cr, x + shadow_offset, y + shadow_offset + shadow_blur, width, height, radius);
    cairo_fill(cr);
    cairo_restore(cr);

    /* --- Výplň pozadí rámečku --- */
    cairo_save(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    /* příklad výplně: poloprůhledné černé pozadí; změň na libovolnou barvu */
    cairo_set_source_rgba(cr, 0.06, 0.06, 0.06, 0.0); /* tmavé pozadí s alfa */
    rounded_rectangle(cr, x, y, width, height, radius);
    cairo_fill(cr);
    cairo_restore(cr);

    /* --- Ohraničení (stroke) --- */
    cairo_save(cr);
    cairo_set_line_width(cr, stroke_width);
    /* barva ohraničení */
    cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.7); /* jemné světlé ohraničení */
    rounded_rectangle(cr, x + stroke_width/2.0, y + stroke_width/2.0, width - stroke_width, height - stroke_width, radius);
    cairo_stroke(cr);
    cairo_restore(cr);
}

/* Hlavní funkce: vykreslí rámeček s jemným stínem a ohraničením */
void draw_frame_2nd(cairo_t *cr)
{
    /* Parametry rámečku - uprav podle potřeby */
    const double x = 25.0;
    const double y = 105.0;
    const double width = 430.0;
    const double height = 50.0;
    const double radius = 10.0;
    const double shadow_offset = 3.0;
    const double shadow_blur = 0.0; /* jednoduchý posun stínu bez rozmazání */
    const double stroke_width = 1.0;

    /* --- Stín (jednoduchý posun + průhledná černá) --- */
    cairo_save(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.35); /* černý stín s alfa */
    rounded_rectangle(cr, x + shadow_offset, y + shadow_offset + shadow_blur, width, height, radius);
    cairo_fill(cr);
    cairo_restore(cr);

    /* --- Výplň pozadí rámečku --- */
    cairo_save(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    /* příklad výplně: poloprůhledné černé pozadí; změň na libovolnou barvu */
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.1); /* tmavé pozadí s alfa */
    rounded_rectangle(cr, x, y, width, height, radius);
    cairo_fill(cr);
    cairo_restore(cr);

    /* --- Ohraničení (stroke) --- */
    cairo_save(cr);
    cairo_set_line_width(cr, stroke_width);
    /* barva ohraničení */
    cairo_set_source_rgba(cr, 0.8, 0.8, 0.2, 1.0); /* jemné světlé ohraničení */
    rounded_rectangle(cr, x + stroke_width/2.0, y + stroke_width/2.0, width - stroke_width, height - stroke_width, radius);
    cairo_stroke(cr);
    cairo_restore(cr);
}

/* nakreslí vodorovnou čáru */
void draw_line_h(cairo_t *cr) {

    /* Stín */
    cairo_save(cr);
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.55); /* černý stín s alfa */
    cairo_set_line_width(cr, 1.5);             /* tloušťka 1.5 px */
    cairo_move_to(cr, 72.0, 42.0);
    cairo_line_to(cr, 402.0, 42.0);
    cairo_stroke(cr);
    cairo_restore(cr);

    /* Line */
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.5);
    cairo_set_line_width(cr, 1.0);             /* tloušťka 1 px */
    cairo_move_to(cr, 70.0, 40.0);
    cairo_line_to(cr, 400.0, 40.0);
    cairo_stroke(cr);

}

/* nakreslí svislou čáru  */
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


/* kreslí plný kruh s obrysem */
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

/* kreslí triangl */
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
