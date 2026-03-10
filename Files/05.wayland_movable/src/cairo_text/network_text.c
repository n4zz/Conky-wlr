#include "network_text.h"
#include "../utils/helper_function.h"
#include <stdio.h>


/*---------------------------------------------------------------------------------------------*/
//*    * N E T W O R K *
/*---------------------------------------------------------------------------------------------*/

void draw_network_header(cairo_t *cr, struct rect bounds)
{
    cairo_save(cr);
    cairo_set_source_rgba(cr, 0.7, 0.9, 1.0, 1.0); //světle modrá
    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14.0);

    cairo_move_to(cr, bounds.x + 210, bounds.y + 0);
    cairo_show_text(cr, " * N E T * ");
    cairo_restore(cr);
}

/* Network interface info */
void draw_network_interface(cairo_t *cr, struct network_stat *net, struct rect bounds)
{
    if (!net->valid) return;

    cairo_save(cr);

    char buf[64];
    snprintf(buf, sizeof(buf), "%s: %s",
             get_iface_type(net->interface),
             net->is_connected ? "ONLINE" : "OFFLINE");

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 13.0);

    if (net->is_connected) {
        cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);  // cyan
    } else {
        cairo_set_source_rgb(cr, 1.0, 0.2, 0.2);  // Červená
    }

    cairo_move_to(cr, bounds.x + 195, bounds.y + 20);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

void draw_ip_text(cairo_t *cr, const struct network_stat *ip, struct rect bounds)
{
    if (!ip->valid)
        return;

    cairo_save(cr);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 15.0);
    /* Shadow*/
    /*cairo_set_source_rgba(cr, 1, 1, 1, 0.5);
    cairo_move_to(cr, bounds.x + 181, bounds.y + 51);
    cairo_show_text(cr, ip->address);*/

    cairo_set_font_size(cr, 15.0);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, bounds.x + 180, bounds.y + 50);
    cairo_show_text(cr, ip->address);
    cairo_restore(cr);
}

/* WiFi síla signálu */
void draw_wifi_signal(cairo_t *cr, struct network_stat *net, struct rect bounds)
{
    if (!net->valid || !net->is_wifi || !net->is_connected) return;

    cairo_save(cr);

    char buf[64];
    snprintf(buf, sizeof(buf), "Signal: %d%% (%d dBm)",
             net->signal_percent, net->signal_strength);

    cairo_select_font_face(cr, "Orbitron", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 12.0);

    // Barevné kódování podle síly signálu
    if (net->signal_percent >= 70) {
        cairo_set_source_rgb(cr, 0.2, 1.0, 0.2);  // Zelená (dobrý)
    } else if (net->signal_percent >= 40) {
        cairo_set_source_rgb(cr, 1.0, 0.8, 0.2);  // Žlutá (střední)
    } else {
        cairo_set_source_rgb(cr, 1.0, 0.2, 0.2);  // Červená (slabý)
    }

    cairo_move_to(cr, bounds.x + 165, bounds.y + 80);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

/* Network rychlost (download) */
void draw_network_d_speed(cairo_t *cr, struct network_stat *net, struct rect bounds)
{
    if (!net->valid) return;

    cairo_save(cr);

    char value[32];
    format_speed_kbps(net->rx_speed_kbps, value, sizeof(value));

    char buf[64];
    snprintf(buf, sizeof(buf), "Down_speed: %s", value);

    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 0.2, 1.0, 0.7);

    cairo_move_to(cr, bounds.x + 10, bounds.y + 120);
    cairo_show_text(cr, buf);

    cairo_restore(cr);
}

/* Network rychlost (upload) */
void draw_network_u_speed(cairo_t *cr, struct network_stat *net, struct rect bounds)
{
    if (!net->valid) return;

    cairo_save(cr);

    char value[32];
    format_speed_kbps(net->tx_speed_kbps, value, sizeof(value));

    char buf[64];
    snprintf(buf, sizeof(buf), "Up_speed: %s", value);

    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 1.0, 0.5, 0.3);

    cairo_move_to(cr, bounds.x + 320, bounds.y + 120);
    cairo_show_text(cr, buf);

    cairo_restore(cr);
}

/* Network celkový přenos download*/
void draw_network_total_down(cairo_t *cr, struct network_stat *net, struct rect bounds)
{
    if (!net->valid) return;

    cairo_save(cr);

    char rx_str[64];
    format_bytes(net->rx_bytes, rx_str, sizeof(rx_str));

    char buf[128];
    snprintf(buf, sizeof(buf), "Total: Down %s", rx_str);

    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);

    cairo_move_to(cr, bounds.x + 10, bounds.y + 195);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}

/* Network celkový přenos upload*/
void draw_network_total_up(cairo_t *cr, struct network_stat *net, struct rect bounds)
{
    if (!net->valid) return;

    cairo_save(cr);

    char tx_str[64];
    format_bytes(net->tx_bytes, tx_str, sizeof(tx_str));

    char buf[128];
    snprintf(buf, sizeof(buf), "Total: Up %s", tx_str);

    cairo_set_font_size(cr, 12.0);
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);

    cairo_move_to(cr, bounds.x + 320, bounds.y + 195);
    cairo_show_text(cr, buf);
    cairo_restore(cr);
}
