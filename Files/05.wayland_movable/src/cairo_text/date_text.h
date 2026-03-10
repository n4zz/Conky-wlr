#ifndef DATE_TEXT_H
#define DATE_TEXT_H

#include "../ui/ui_rect.h"
#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
/* Draw current date (e.g., Monday 14 Dec 2025) */
/*---------------------------------------------------------------------------------------------*/
void draw_date_text(cairo_t *cr, struct rect bounds);


#endif
