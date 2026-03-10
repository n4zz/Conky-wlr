#ifndef SYS_INFO_STATIC_TEXT_H
#define SYS_INFO_STATIC_TEXT_H

#include "../ui/ui_rect.h"
#include "../system_info/system_info_static.h"
#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
/* Draw System information Static 1 Line */
/*---------------------------------------------------------------------------------------------*/
void draw_system_info_oneline(cairo_t *cr, struct system_info_static *info, struct rect bounds);



#endif
