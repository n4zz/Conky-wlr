#ifndef STORAGE_TEXT_H
#define STORAGE_TEXT_H

#include "../ui/ui_rect.h"
#include "../system_info/storage_monitor.h"
#include <cairo/cairo.h>

/*---------------------------------------------------------------------------------------------*/
// STORAGE
/*---------------------------------------------------------------------------------------------*/

void draw_disk_header(cairo_t *cr, struct rect bounds);
/* Disk name (mount point )*/
void draw_disk_name(cairo_t *cr, struct disk_stat *disk, struct rect bounds);

/* Draw Disk usages (use/total) */
void draw_disk_usage(cairo_t *cr, struct disk_stat *disk, struct rect bounds);

/* Draw Disk free */
void draw_disk_total(cairo_t *cr, struct disk_stat *disk, struct rect bounds);

/* Draw Disk free */
void draw_disk_used(cairo_t *cr, struct disk_stat *disk, struct rect bounds);

/* Draw Disk free */
void draw_disk_free(cairo_t *cr, struct disk_stat *disk, struct rect bounds);

/* Draw Disk percent */
void draw_disk_percent(cairo_t *cr, struct disk_stat *disk, struct rect bounds);

/* Draw Disk I/O speed read */
void draw_disk_io_speed_read(cairo_t *cr, struct disk_stat *disk, struct rect bounds);

/* Draw Disk I/O speed write */
void draw_disk_io_speed_write(cairo_t *cr, struct disk_stat *disk, struct rect bounds);

/* Draw Disk I/O speed total */
void draw_disk_io_total(cairo_t *cr, struct disk_stat *disk, struct rect bounds);


#endif
