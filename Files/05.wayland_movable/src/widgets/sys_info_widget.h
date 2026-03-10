#pragma once
#include <cairo/cairo.h>
#include "../ui/ui_context.h"
#include "../ui/ui_rect.h"

void draw_sys_info_widget(cairo_t *cr, struct ui_context *ctx, struct rect bounds);
