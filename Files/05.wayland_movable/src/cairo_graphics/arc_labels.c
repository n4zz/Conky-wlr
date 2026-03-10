#include "arc_labels.h"
#include <cairo/cairo.h>
#include <stdio.h>
#include <math.h>

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
)
{
    if (num_labels <= 0)
        return;

    cairo_save(cr);

    cairo_set_source_rgb(cr, r, g, b);
    cairo_select_font_face(cr, "Sans",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, font_size);

    for (int i = 0; i < num_labels; i++) {
        double t = (double)i / (num_labels - 1);
        double angle = start_angle + (end_angle - start_angle) * t;

        double text_radius = radius + offset;
        double tx = x + text_radius * cos(angle);
        double ty = y + text_radius * sin(angle);

        char label[16];
        snprintf(label, sizeof(label), "%d%%", (int)(t * 100));

        cairo_text_extents_t ext;
        cairo_text_extents(cr, label, &ext);

        cairo_move_to(cr,
            tx - ext.width / 2.0 - ext.x_bearing,
            ty - ext.height / 2.0 - ext.y_bearing
        );

        cairo_show_text(cr, label);
    }

    cairo_restore(cr);
}
