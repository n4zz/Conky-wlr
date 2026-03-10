#ifndef HEXAGON_PROGRESS_H
#define HEXAGON_PROGRESS_H

#include <cairo/cairo.h>

typedef struct {
    struct { double r, g, b, a; } frame_color;

    double size;   // velikost (vzdálenost od středu k vrcholu)
    double line_width;   // tloušťka čáry

    struct { double r, g, b, a; } bg;
    struct { double r, g, b; } fg;
}
hexagon_bar_t;


/*---------------------------------------------------------------------------------------------*/
//*     HEXAGON PROGRESSBAR
/*---------------------------------------------------------------------------------------------*/

void draw_hexagon_progress(
    cairo_t *cr,
    double x, double y,        // střed hexagonu
    double value,              // 0-100%
    const hexagon_bar_t *style
);

typedef struct {
    double size;
    double line_width;
    int count;          // počet labelů
    const char **text;  // pole textů
}

labels_t;

void draw_hexagon_labels(
    cairo_t *cr,
    double x, double y,        // střed hexagonu
    const labels_t *style
);

#endif
