#ifndef NETWORK_TEXT_H
#define NETWORK_TEXT_H

#include "../ui/ui_rect.h"
#include "../system_info/network_monitor.h"
#include <cairo/cairo.h>


/*---------------------------------------------------------------------------------------------*/
//   NETWORK
/*---------------------------------------------------------------------------------------------*/

void draw_network_header(cairo_t *cr, struct rect bounds);
/* Draw Network interface info */
void draw_network_interface(cairo_t *cr, struct network_stat *net, struct rect bounds);

/* Draw IP Address */
void draw_ip_text(cairo_t *cr, const struct network_stat *ip, struct rect bounds);

/* Draw WiFi strenght signal */
void draw_wifi_signal(cairo_t *cr, struct network_stat *net, struct rect bounds);

/* Draw Network speed (download) */
void draw_network_d_speed(cairo_t *cr, struct network_stat *net, struct rect bounds);

/* Draw Network speed (upload) */
void draw_network_u_speed(cairo_t *cr, struct network_stat *net, struct rect bounds);

/* Draw Total Network down */
void draw_network_total_down(cairo_t *cr, struct network_stat *net, struct rect bounds);

/* Draw Total Network up */
void draw_network_total_up(cairo_t *cr, struct network_stat *net, struct rect bounds);


#endif
