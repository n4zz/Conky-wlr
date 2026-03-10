#ifndef WIDGET_H
#define WIDGET_H

#include "../ui/ui_context.h"
#include "../ui/ui_rect.h"
#include <cairo/cairo.h>

typedef void (*widget_draw_fn)(cairo_t *cr, struct ui_context *ctx, struct rect bounds);

struct widget {
    widget_draw_fn draw1;
    widget_draw_fn draw2;   // může být NULL
    struct rect bounds;
};

#endif
