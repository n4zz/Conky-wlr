#pragma once
#include <cairo/cairo.h>
#include "../config/progressbars_init.h"

#include "../cairo_graphics/horizontal_bar.h"

#include "../ui/ui_context.h"
#include "../ui/ui_rect.h"


void draw_ram_widget(cairo_t *cr, struct ui_context *ctx, struct rect bounds);
