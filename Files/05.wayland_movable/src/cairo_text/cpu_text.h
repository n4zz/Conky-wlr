#ifndef CPU_TEXT_H
#define CPU_TEXT_H

#include "../ui/ui_rect.h"
#include "../system_info/cpu_monitor.h"
#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
// CPU
/*---------------------------------------------------------------------------------------------*/

void draw_cpu_header(cairo_t *cr, struct rect bounds);
/* Draw current CPU - usage */
void draw_cpu_usage(cairo_t *cr, double usage, struct rect bounds);

/* Draw  CPU frekvency */
void draw_cpu_frequency(cairo_t *cr, double freq_mhz, struct rect bounds);

/* Draw  CPU temperature */
void draw_cpu_temperature(cairo_t *cr, double temp_celsius, struct rect bounds);


#endif
