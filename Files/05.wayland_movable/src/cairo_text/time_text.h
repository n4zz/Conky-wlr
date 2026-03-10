#ifndef TIME_TEXT_H
#define TIME_TEXT_H

#include "../ui/ui_rect.h"
#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
/* Draw current time (HH:MM:SS) */
/*---------------------------------------------------------------------------------------------*/
void draw_current_time(cairo_t *cr, struct rect bounds);

#endif
