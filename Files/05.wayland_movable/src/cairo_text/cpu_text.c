#include "cpu_text.h"
#include "../ui/ui_rect.h"
#include "../utils/helper_function.h"
#include <stdio.h>

//*---------------------------------------------------------------------------------------------*/
//*    * C P U *
/*---------------------------------------------------------------------------------------------*/

void draw_cpu_header(cairo_t *cr, struct rect bounds)
{
    cairo_save(cr);
    cairo_set_source_rgba(cr, 0.7, 0.9, 1.0, 1.0); //světle modrá
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14.0);

    cairo_move_to(cr, bounds.x + 210, bounds.y + 5);
    cairo_show_text(cr, " * C P U * ");
    cairo_restore(cr);
}

/*     CPU  USAGE %    */
void draw_cpu_usage(cairo_t *cr, double usage, struct rect bounds)
{
    cairo_save(cr);
    char buf[64];
    //snprintf(buf, sizeof(buf), "CPU:  %.1f %%", usage);
    snprintf(buf, sizeof(buf), "%.1f %%", usage);

    cairo_set_font_size(cr, 14.0);
    cairo_set_source_rgb(cr, 0.2, 1.0, 0.2);

    cairo_move_to(cr, bounds.x + 30, bounds.y + 70);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

/*     CPU frekvence */
void draw_cpu_frequency(cairo_t *cr, double freq_mhz, struct rect bounds)
{
    cairo_save(cr);

    char value[32];
    format_mhz_or_ghz(freq_mhz, value, sizeof(value));

    char buf[64];
    snprintf(buf, sizeof(buf), "%s", value);

    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);

    cairo_move_to(cr, bounds.x + 30, bounds.y + 90);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

/*     CPU teplota */
void draw_cpu_temperature(cairo_t *cr, double temp_celsius, struct rect bounds)
{
    cairo_save(cr);
    char buf[64];
    snprintf(buf, sizeof(buf), "%.1f °C", temp_celsius);

    cairo_set_font_size(cr, 14.0);

    // Barevné kódování podle teploty
    if (temp_celsius < 50.0) {
        cairo_set_source_rgb(cr, 0.2, 1.0, 0.2);  // Zelená (studená)
    } else if (temp_celsius < 70.0) {
        cairo_set_source_rgb(cr, 1.0, 0.8, 0.2);  // Žlutá (teplá)
    } else {
        cairo_set_source_rgb(cr, 1.0, 0.2, 0.2);  // Červená (horká)
    }

    cairo_move_to(cr, bounds.x + 30, bounds.y + 110);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}
