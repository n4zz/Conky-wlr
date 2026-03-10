#include "gpu_text.h"
#include <stdio.h>

/*---------------------------------------------------------------------------------------------*/
//*    * G P U *
/*---------------------------------------------------------------------------------------------*/

void draw_gpu_header(cairo_t *cr, struct rect bounds)
{
    cairo_save(cr);
    cairo_set_source_rgba(cr, 0.7, 0.9, 1.0, 1.0); //světle modrá
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14.0);

    cairo_move_to(cr, bounds.x + 210, bounds.y + 5);
    cairo_show_text(cr, " * G P U * ");
    cairo_restore(cr);
}

void draw_gpu_usage(cairo_t *cr, double usage_percent, struct rect bounds)
{
    char buf[64];
    //snprintf(buf, sizeof(buf), "GPU load: %.1f %%", usage_percent);
    snprintf(buf, sizeof(buf), "%.1f %%", usage_percent);


    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.2, 0.6, 1.0);
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 14.0);

    cairo_move_to(cr, bounds.x + 30  , bounds.y + 70);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

void draw_gpu_temperature(cairo_t *cr, double temp_celsius,struct rect bounds)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "GPU temp: %.1f °C", temp_celsius);

    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.2, 0.6, 1.0);
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12.0);

    cairo_move_to(cr, bounds.x + 30, bounds.y + 70);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

void draw_gpu_memory_usage(cairo_t *cr, double mem_used_percent, struct rect bounds)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "VRAM: %.1f %%", mem_used_percent);

    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.2, 0.6, 0.7);
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 11.0);

    cairo_move_to(cr, bounds.x +30 , bounds.y + 100);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

void draw_gpu_frequency_core(cairo_t *cr, double freq_mhz, struct rect bounds)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "CORE: %.0f MHz", freq_mhz);

    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.2, 0.6, 0.7);
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 11.0);

    cairo_move_to(cr, bounds.x + 130, bounds.y + 100);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

void draw_gpu_frequency_mem(cairo_t *cr, double freq_mhz, struct rect bounds)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "MEM:  %.0f MHz", freq_mhz);

    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.2, 0.6, 0.7);
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 11.0);

    cairo_move_to(cr, bounds.x + 240, bounds.y + 100);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

void draw_gpu_power(cairo_t *cr, double power_watt, struct rect bounds)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "POWER: %.1f W", power_watt);

    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.2, 0.6, 0.7);
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 11.0);

   cairo_move_to(cr, bounds.x + 360, bounds.y + 100);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}
