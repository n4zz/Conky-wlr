#define _USE_MATH_DEFINES
#include <math.h>
#include <cairo/cairo.h>
#include <stdint.h>
#include <time.h>
#include "clock.h"
//#include "widget.h"
#include "../ui/ui_rect.h"

void draw_neon_clock(cairo_t *cr, struct ui_context *ctx, struct rect bounds)
{
    (void)ctx;
    // Střed a radius
    double radius = bounds.w / 1.0;
    double x = bounds.x + radius;
    double y = bounds.y + radius;

    cairo_new_path(cr);
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    int h = t->tm_hour;
    int m = t->tm_min;
    int s = t->tm_sec;

    // Výpočet úhlů
    double hour_angle   = (h % 12) * 30 + m * 0.5;
    double minute_angle = m * 6;
    double second_angle = s * 6;

    double hour_rad   = (hour_angle   - 90) * M_PI / 180.0;
    double minute_rad = (minute_angle - 90) * M_PI / 180.0;
    double second_rad = (second_angle - 90) * M_PI / 180.0;

    // === NEON GLOW CIFERNÍKU ===
    cairo_save(cr);
    cairo_set_line_width(cr, 8);
    cairo_set_source_rgba(cr, 0.0, 1.0, 1.0, 0.20);
    cairo_arc(cr, x, y, radius, 0, 2 * M_PI);
    cairo_stroke(cr);
    cairo_restore(cr);

    // === OSTRÝ CIFERNÍK ===
    cairo_save(cr);
    cairo_set_line_width(cr, 2);
    cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);
    cairo_arc(cr, x, y, radius, 0, 2 * M_PI);
    cairo_stroke(cr);
    cairo_restore(cr);

    // === HODINOVÁ RUČIČKA ===
    cairo_save(cr);
    cairo_set_line_width(cr, 6);
    cairo_set_source_rgba(cr, 0.0, 1.0, 1.0, 0.25);
    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x + cos(hour_rad) * (radius * 0.5),
                       y + sin(hour_rad) * (radius * 0.5));
    cairo_stroke(cr);
    cairo_restore(cr);

    cairo_save(cr);
    cairo_set_line_width(cr, 2);
    cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);
    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x + cos(hour_rad) * (radius * 0.5),
                       y + sin(hour_rad) * (radius * 0.5));
    cairo_stroke(cr);
    cairo_restore(cr);

    // === MINUTOVÁ RUČIČKA ===
    cairo_save(cr);
    cairo_set_line_width(cr, 5);
    cairo_set_source_rgba(cr, 0.0, 1.0, 1.0, 0.25);
    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x + cos(minute_rad) * (radius * 0.75),
                       y + sin(minute_rad) * (radius * 0.75));
    cairo_stroke(cr);
    cairo_restore(cr);

    cairo_save(cr);
    cairo_set_line_width(cr, 1.5);
    cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);
    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x + cos(minute_rad) * (radius * 0.75),
                       y + sin(minute_rad) * (radius * 0.75));
    cairo_stroke(cr);
    cairo_restore(cr);

    // === SEKUNDOVÁ RUČIČKA ===
    cairo_save(cr);
    cairo_set_line_width(cr, 1);
    cairo_set_source_rgb(cr, 1.0, 0.2, 0.2);
    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x + cos(second_rad) * (radius * 0.9),
                       y + sin(second_rad) * (radius * 0.9));
    cairo_stroke(cr);
    cairo_restore(cr);

    // Střed
    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);
    cairo_arc(cr, x, y, 2.0, 0, 2.0 * M_PI);
    cairo_fill(cr);
    cairo_restore(cr);
}

void draw_neon_clock_marks(cairo_t *cr, struct ui_context *ctx, struct rect bounds)
{
    (void)ctx;
    double radius = bounds.w / 1.0;
    double x = bounds.x + radius;
    double y = bounds.y + radius;

    cairo_save(cr);

    int marks = 12;
    double inner = radius * 0.82;
    double outer = radius * 0.92;

    for (int i = 0; i < marks; i++) {
        double angle_deg = i * 30.0;
        double angle = (angle_deg - 90) * M_PI / 180.0;

        double x1 = x + cos(angle) * inner;
        double y1 = y + sin(angle) * inner;
        double x2 = x + cos(angle) * outer;
        double y2 = y + sin(angle) * outer;

        // Glow
        cairo_set_line_width(cr, 6);
        cairo_set_source_rgba(cr, 0.0, 1.0, 1.0, 0.25);
        cairo_move_to(cr, x1, y1);
        cairo_line_to(cr, x2, y2);
        cairo_stroke(cr);

        // Core
        cairo_set_line_width(cr, 2);
        cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);
        cairo_move_to(cr, x1, y1);
        cairo_line_to(cr, x2, y2);
        cairo_stroke(cr);
    }

    cairo_restore(cr);
}
