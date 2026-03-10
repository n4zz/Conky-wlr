#ifndef ARC_LABELS_H
#define ARC_LABELS_H

#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
//*     GAUGE LABELS
/*---------------------------------------------------------------------------------------------*/
void draw_arc_labels(
    cairo_t *cr,
    double x, double y,          // střed
    double radius,               // poloměr
    double font_size,            // velikost textu
    double offset,               // vzdálenost od oblouku
    int num_labels,              // počet labelů
    double start_angle,          // začátek oblouku
    double end_angle,            // konec oblouku
    double r, double g, double b // barva textu
);

#endif
