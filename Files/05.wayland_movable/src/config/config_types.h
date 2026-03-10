/*
 * config_types.h
 * -------------------------------------------
 * Struktury pro konfiguraci aplikace
 */

#ifndef CONFIG_TYPES_H
#define CONFIG_TYPES_H

#include <stdbool.h>

/*---------------------------------------------------------------------------------------------*/
// RGB(A) barva
/*---------------------------------------------------------------------------------------------*/
struct color_rgba {
    double r, g, b, a;
};

/*---------------------------------------------------------------------------------------------*/
// Widget pozice a viditelnost
/*---------------------------------------------------------------------------------------------*/
struct widget_config {
    bool enabled;
    double x, y;
    double width, height;
};

/*---------------------------------------------------------------------------------------------*/
// Graf konfigurace
/*---------------------------------------------------------------------------------------------*/
struct graph_config {
    struct color_rgba line_color;
    struct color_rgba fill_top;
    struct color_rgba fill_bottom;
};

/*---------------------------------------------------------------------------------------------*/
// Text konfigurace
/*---------------------------------------------------------------------------------------------*/
struct text_config {
    char font_family[64];
    double font_size;
    struct color_rgba color;
};

/*---------------------------------------------------------------------------------------------*/
// Hlavní config struktura
/*---------------------------------------------------------------------------------------------*/
struct app_config {
    // Wayland Surface Window
    struct {
        int width;
        int height;
    } surface_window;

    /* Main window (dashboard window) */
    struct {
        double x, y;              // pozice
        double width, height;     // rozměry
        double corner_radius;     // zaoblení rohů
        double shadow_offset;     // posun stínu
        double shadow_blur;       // rozmazání stínu
        double shadow_alpha;      // průhlednost stínu
        double stroke_width;      // šířka rámečku

        // Barvy
        struct color_rgba bg_color;      // pozadí
        struct color_rgba stroke_color;  // rámeček
        struct color_rgba shadow_color;  // stín

        // stín pozadí
        struct {
            double offset, blur, alpha;
            struct color_rgba color;
        } shadow_fill;

         // stín rámečku
        struct {
            double offset, blur, alpha;
            struct color_rgba color;
        } shadow_stroke;


    } main_window;
    
    // Widgets pozice
    struct {
        struct widget_config sysinfo;
        struct widget_config cpu;
        struct widget_config gpu;
        struct widget_config ram;
        struct widget_config storage;
        struct widget_config network;
        struct widget_config clock;
    } widgets;
    
    // Grafy
    struct {
        struct graph_config cpu;
        struct graph_config gpu;
        struct graph_config ram;
        struct graph_config disk_read;
        struct graph_config disk_write;
        struct graph_config net_rx;
        struct graph_config net_tx;
    } graphs;
    
    // Text styling
    struct {
        struct text_config cpu_header;
        struct text_config cpu_usage;
        struct text_config gpu_header;
        struct text_config ram_header;

    } text;
    
    // Network
    struct {
        bool auto_detect;
        char interface[64];
    } network;
};

/*---------------------------------------------------------------------------------------------*/
// Globální config instance (definovaná v config_loader.c)
/*---------------------------------------------------------------------------------------------*/
extern struct app_config g_config;

#endif /* CONFIG_TYPES_H */
