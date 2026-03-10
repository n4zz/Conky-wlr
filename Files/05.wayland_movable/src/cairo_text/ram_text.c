#include "ram_text.h"
#include "../utils/helper_function.h"
#include <stdio.h>

/*---------------------------------------------------------------------------------------------*/
/*     RAM      */
/*---------------------------------------------------------------------------------------------*/

void draw_ram_header(cairo_t *cr, struct rect bounds)
{
    cairo_save(cr);
    cairo_set_source_rgba(cr, 0.7, 0.9, 1.0, 1.0); //světle modrá
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14.0);

    cairo_move_to(cr, bounds.x + 210, bounds.y + 0);
    cairo_show_text(cr, " * R A M * ");
    cairo_restore(cr);
}

/* Ram total */
void draw_ram_total(cairo_t *cr, const struct ram_stat *ram, struct rect bounds)
{
    double total_mb = ram->total_kb / 1024.0;
    cairo_save(cr);
    char value[32];
    format_mb_or_gb(total_mb, value, sizeof(value));

    char buf[64];
    snprintf(buf, sizeof(buf),"Total: %s" , value);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12.0);

    cairo_move_to(cr, bounds.x + 30, bounds.y + 10);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

/* Ram used */
void draw_ram_used(cairo_t *cr, const struct ram_stat *ram, struct rect bounds)
{
    double used_mb = ram->used_kb / 1024.0;
    cairo_save(cr);
    char value[32];
    format_mb_or_gb(used_mb, value, sizeof(value));

    char buf[64];
    snprintf(buf, sizeof(buf),"Used: %s" , value);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12.0);

    cairo_move_to(cr, bounds.x + 30, bounds.y + 30);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

void draw_ram_percent(cairo_t *cr, const struct ram_stat *ram, struct rect bounds)
{
    cairo_save(cr);
    char buf[64];
    snprintf(buf, sizeof(buf), "%.1f%%", ram->percent);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12.0);

    cairo_move_to(cr, bounds.x + 380, bounds.y + 20);  // pod draw_ram_text()
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}
