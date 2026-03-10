#ifndef CLOCK_H
#define CLOCK_H

#include <cairo/cairo.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "widget.h"
#include "../ui/ui_rect.h"

void draw_neon_clock(cairo_t *cr, struct ui_context *ctx, struct rect bounds);

void draw_neon_clock_marks(cairo_t *cr, struct ui_context *ctx, struct rect bounds);

#endif
