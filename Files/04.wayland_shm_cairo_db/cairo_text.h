#ifndef CAIRO_TEXT_H
#define CAIRO_TEXT_H

#include "system_variables.h"
#include <cairo/cairo.h>

/* Draw current date (e.g., Monday 14 Dec 2025) */
void draw_date_text(cairo_t *cr);

/* Draw main static messages */
void draw_main_text(cairo_t *cr);

/* Draw current time (HH:MM:SS) */
void draw_current_time(cairo_t *cr);

/* Draw current CPU - usage */
void draw_cpu_usage(cairo_t *cr, double usage);

/* Draw current RAM - usage */
void draw_ram_text(cairo_t *cr, const struct ram_stat *ram);

#endif


