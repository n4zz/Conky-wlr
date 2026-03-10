#include "storage_text.h"
#include "../utils/helper_function.h"
#include <stdio.h>

/*---------------------------------------------------------------------------------------------*/
//    STORAGE
/*---------------------------------------------------------------------------------------------*/

void draw_disk_header(cairo_t *cr, struct rect bounds)
{
    cairo_save(cr);
    cairo_set_source_rgba(cr, 0.7, 0.9, 1.0, 1.0); //světle modrá
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14.0);

    cairo_move_to(cr, bounds.x + 207, bounds.y + 0);
    cairo_show_text(cr, " * D I S K * ");
    cairo_restore(cr);
}

/* Disk name (mount point )*/
void draw_disk_name(cairo_t *cr, struct disk_stat *disk, struct rect bounds)
{
    cairo_save(cr);
    if (!disk->valid) return;

    char buf[320];
    snprintf(buf, sizeof(buf), "Disk: %s", disk->mount_point);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 13.0);
    cairo_set_source_rgb(cr, 1.0, 0.8, 0.2);  // Žlutá pro název

    cairo_move_to(cr, bounds.x + 30, bounds.y + 20);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

/* Disk celkem */
void draw_disk_total(cairo_t *cr, struct disk_stat *disk, struct rect bounds)
{
    cairo_save(cr);
    if (!disk->valid) return;

    char value[32];
    format_mb_or_gb(disk->total_mb, value, sizeof(value));

    char buf[64];
    snprintf(buf, sizeof(buf), "Total: %s", value);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);

    cairo_move_to(cr, bounds.x + 30, bounds.y + 40);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

/* Disk použité místo */
void draw_disk_used(cairo_t *cr, struct disk_stat *disk, struct rect bounds)
{
    cairo_save(cr);
    if (!disk->valid) return;

    char value[32];
    format_mb_or_gb(disk->used_mb, value, sizeof(value));

    char buf[64];
    snprintf(buf, sizeof(buf), "Used: %s", value);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);

    cairo_move_to(cr, bounds.x + 360, bounds.y + 40);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

/* Disk volné místo */
void draw_disk_free(cairo_t *cr, struct disk_stat *disk, struct rect bounds)
{
    cairo_save(cr);
    if (!disk->valid) return;

    char value[32];
    format_mb_or_gb(disk->free_mb, value, sizeof(value));

    char buf[64];
    snprintf(buf, sizeof(buf), "Free: %s", value);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);

    cairo_move_to(cr, bounds.x + 200, bounds.y + 40);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

/* Disk procenta */
void draw_disk_percent(cairo_t *cr, struct disk_stat *disk, struct rect bounds)
{
    if (!disk->valid) return;

    char buf[64];
    snprintf(buf, sizeof(buf), "%.1f %%", disk->percent);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 1.0, 0.8, 0.2);  // Žlutá

    cairo_move_to(cr, bounds.x + 380, bounds.y + 20);
    cairo_show_text(cr, buf);
}

/* Disk I/O speed read */
void draw_disk_io_speed_read(cairo_t *cr, struct disk_stat *disk, struct rect bounds)
{
    if (!disk->valid) return;

    char buf[128];
    snprintf(buf, sizeof(buf), "Read: %.1f KB/s",
             disk->read_speed_kbps);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 0.2, 1.0, 0.7);

    cairo_move_to(cr, bounds.x + 10, bounds.y + 130);
    cairo_show_text(cr, buf);
}

/* Disk I/O speed write */
void draw_disk_io_speed_write(cairo_t *cr, struct disk_stat *disk, struct rect bounds)
{
    if (!disk->valid) return;

    char buf[128];
    snprintf(buf, sizeof(buf), "Write: %.1f KB/s",
             disk->write_speed_kbps);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 1.0, 0.5, 0.3);

    cairo_move_to(cr, bounds.x + 320, bounds.y + 130);
    cairo_show_text(cr, buf);
}

/* Disk I/O total */
void draw_disk_io_total(cairo_t *cr, struct disk_stat *disk, struct rect bounds)
{
    if (!disk->valid) return;

    char read_str[64], write_str[64];
    format_bytes(disk->read_bytes, read_str, sizeof(read_str));
    format_bytes(disk->write_bytes, write_str, sizeof(write_str));

    char buf[256];
    snprintf(buf, sizeof(buf), "Total: R %s  W %s", read_str, write_str);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 11.0);
    cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);

    cairo_move_to(cr, bounds.x + 160, bounds.y + 210);
    cairo_show_text(cr, buf);
}
