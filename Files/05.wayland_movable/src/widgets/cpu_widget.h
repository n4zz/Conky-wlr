#pragma once
#include <cairo/cairo.h>
#include "../ui/ui_rect.h"
#include "../ui/ui_context.h"
#include "../cairo_graphics/arc_labels.h"

void draw_cpu_widget(cairo_t *cr, struct ui_context *ctx, struct rect bounds);

