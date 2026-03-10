#ifndef RAM_TEXT_H
#define RAM_TEXT_H

#include "../ui/ui_rect.h"
#include "../system_info/ram_monitor.h"
#include <cairo/cairo.h>


/*---------------------------------------------------------------------------------------------*/
//    RAM
/*---------------------------------------------------------------------------------------------*/

void draw_ram_header(cairo_t *cr, struct rect bounds);

/* Draw current RAM - total */
void draw_ram_total(cairo_t *cr, const struct ram_stat *ram, struct rect bounds);

/* Draw current RAM - usage */
void draw_ram_used(cairo_t *cr, const struct ram_stat *ram, struct rect bounds);

/* Draw current RAM - percent */
void draw_ram_percent(cairo_t *cr, const struct ram_stat *ram, struct rect bounds);


#endif
