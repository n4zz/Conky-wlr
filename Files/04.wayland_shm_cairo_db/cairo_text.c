#include "cairo_text.h"
#include <cairo/cairo.h>
#include <time.h>
#include <stdio.h>
#include <string.h>


/* -------------------- DATE TEXT -------------------- */
void draw_date_text(cairo_t *cr)
{
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

    char date_str[64];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(date_str, sizeof(date_str), "%A %d %b %Y", tm_info);

    cairo_select_font_face(cr, "Sans",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);

    cairo_set_font_size(cr, 15.0);

    /* Draw shadow */
    cairo_set_source_rgba(cr, 0, 0, 0, 0.6);
    cairo_move_to(cr, 32, 72);
    cairo_show_text(cr, date_str);

    /* Draw main text */
    cairo_set_source_rgb(cr, 1.0, 0.5, 0.0);
    cairo_move_to(cr, 30, 70);
    cairo_show_text(cr, date_str);
}

/* -------------------- MAIN TEXT -------------------- */
void draw_main_text(cairo_t *cr)
{
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

    cairo_set_font_size(cr, 20.0);

    /* Draw shadow text */
    cairo_set_source_rgba(cr, 0, 0, 0, 0.6);
    cairo_move_to(cr, 162, 32);
    cairo_show_text(cr, "Hello Wayland!");

    /* Draw main text */
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_move_to(cr, 160, 30);
    cairo_show_text(cr, "Hello Wayland!");

    /* Color test */
    cairo_set_font_size(cr, 24.0);

    cairo_set_source_rgba(cr, 0, 0, 0, 0.6);
    cairo_move_to(cr, 152, 142);
    cairo_show_text(cr, "! CONKY-WLR !");

    cairo_set_source_rgb(cr, 0.8, 0.8, 0.0);
    cairo_move_to(cr, 150, 140);
    cairo_show_text(cr, "! CONKY-WLR !");

    cairo_set_font_size(cr, 15);

    cairo_set_source_rgba(cr, 0, 0, 0, 0.6);
    cairo_move_to(cr, 192, 177);
    cairo_show_text(cr, "comming . . .");

    cairo_set_source_rgb(cr, 0.8, 0.8, 0.0);
    cairo_move_to(cr, 190, 175);
    cairo_show_text(cr, "comming . . .");
}

/* -------------------- CURRENT TIME -------------------- */
void draw_current_time(cairo_t *cr)
{
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

    char time_str[16];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(time_str, sizeof(time_str), "%H : %M : %S", tm_info);

    cairo_select_font_face(cr, "Sans",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_font_size(cr, 20.0);

    /* Draw shadow */
    cairo_set_source_rgba(cr, 0, 0, 0, 0.6);
    cairo_move_to(cr, 342, 72);
    cairo_show_text(cr, time_str);

    /* Draw main text */
    cairo_set_source_rgb(cr, 0.2, 1.0, 0.2);
    cairo_move_to(cr, 340, 70);
    cairo_show_text(cr, time_str);
}

/* -------------------- SYSTEM VARIABLES -----------------
 * -------------------------------------------------------*/

/*     CPU      */
void draw_cpu_usage(cairo_t *cr, double usage)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "CPU: %.1f %%", usage);

    cairo_set_font_size(cr, 15.0);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 40, 200);
    cairo_show_text(cr, buf);
}

/*     RAM      */
void draw_ram_text(cairo_t *cr, const struct ram_stat *ram)
{
    char buf[64];
    snprintf(buf, sizeof(buf),
             "RAM: %lu / %lu MB",
             ram->used_kb / 1024,
             ram->total_kb / 1024);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 40, 220);
    cairo_show_text(cr, buf);
}
