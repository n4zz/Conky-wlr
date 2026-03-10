#ifndef GPU_TEXT_H
#define GPU_TEXT_H

#include "../ui/ui_rect.h"
#include "../system_info/gpu_monitor.h"
#include <cairo/cairo.h>


/*---------------------------------------------------------------------------------------------*/
/* GPU text drawing */
/*---------------------------------------------------------------------------------------------*/

void draw_gpu_header(cairo_t *cr, struct rect bounds);
void draw_gpu_usage(cairo_t *cr, double usage_percent, struct rect bounds);
void draw_gpu_temperature(cairo_t *cr, double temp_celsius, struct rect bounds);
void draw_gpu_memory_usage(cairo_t *cr, double mem_used_percent, struct rect bounds);
void draw_gpu_frequency_core(cairo_t *cr, double freq_mhz, struct rect bounds);
void draw_gpu_frequency_mem(cairo_t *cr, double freq_mhz, struct rect bounds);
void draw_gpu_power(cairo_t *cr, double power_watt, struct rect bounds);


#endif
