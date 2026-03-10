#ifndef ARC_MARKS_H
#define ARC_MARKS_H

#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
// GAUGE MARKS
/*---------------------------------------------------------------------------------------------*/
void draw_arc_marks(
    cairo_t *cr,
    double x, double y,          // střed
    double radius,               // poloměr
    double line_width,           // tloušťka čáry značky
    double mark_lenght,                 // délka značky
    double offset,               // vzdálenost od oblouku
    int num_marks,               // počet značek
    double start_angle,          // začátek oblouku
    double end_angle,            // konec oblouku
    double r, double g, double b // barva značek
);

#endif
