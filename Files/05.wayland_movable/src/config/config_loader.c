/*
 * config_loader.c
 * -------------------------------------------
 * Implementace načítání INI configu
 * Používá jednoduchou vlastní parsovací logiku
 */

#define _GNU_SOURCE
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Globální config instance */
struct app_config g_config;

/*---------------------------------------------------------------------------------------------*/
// Helper funkce
/*---------------------------------------------------------------------------------------------*/

/* Odstranění bílých znaků ze začátku a konce */
static char* trim(char *str)
{
    char *end;
    
    /* Začátek */
    while (isspace((unsigned char)*str)) str++;
    
    if (*str == 0) return str;
    
    /* Konec */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    
    return str;
}

/* Parsování sekce [name] */
static int is_section(const char *line, char *section_name, size_t size)
{
    if (line[0] != '[') return 0;
    
    const char *end = strchr(line, ']');
    if (!end) return 0;
    
    size_t len = end - line - 1;
    if (len >= size) len = size - 1;
    
    strncpy(section_name, line + 1, len);
    section_name[len] = '\0';
    
    return 1;
}

/* Parsování key=value */
static int parse_keyvalue(const char *line, char *key, char *value, size_t size)
{
    const char *eq = strchr(line, '=');
    if (!eq) return 0;
    
    /* Key */
    size_t key_len = eq - line;
    if (key_len >= size) key_len = size - 1;
    strncpy(key, line, key_len);
    key[key_len] = '\0';
    
    /* Value */
    strncpy(value, eq + 1, size - 1);
    value[size - 1] = '\0';
    
    /* Trim oboje */
    strcpy(key, trim(key));
    strcpy(value, trim(value));
    
    return 1;
}

/*---------------------------------------------------------------------------------------------*/
// Default hodnoty
/*---------------------------------------------------------------------------------------------*/

static void config_set_defaults(void)
{
    memset(&g_config, 0, sizeof(g_config));
    
    /* Surface Window */
    g_config.surface_window.width = 520;
    g_config.surface_window.height = 920;

    /* Main Window defaults */
    g_config.main_window.x = 10.0;
    g_config.main_window.y = 5.0;
    g_config.main_window.width = 500.0;
    g_config.main_window.height = 900.0;
    g_config.main_window.corner_radius = 15.0;
    g_config.main_window.shadow_offset = 0.5;
    g_config.main_window.shadow_blur = 0.8;
    g_config.main_window.shadow_alpha = 0.2;
    g_config.main_window.stroke_width = 2.0;

    // Barvy
    g_config.main_window.bg_color = (struct color_rgba){0.0, 0.0, 0.0, 0.5};
    g_config.main_window.stroke_color = (struct color_rgba){0.2, 0.6, 1.0, 1.0};
    g_config.main_window.shadow_color = (struct color_rgba){0.0, 0.6, 0.8, 0.5};

    /* Main window - shadow fill (pozadí) */
    g_config.main_window.shadow_fill.offset = 0.5;
    g_config.main_window.shadow_fill.blur = 0.8;
    g_config.main_window.shadow_fill.alpha = 0.2;
    g_config.main_window.shadow_fill.color = (struct color_rgba){0.0, 0.0, 0.0, 1.0};

    /* Main window - shadow stroke (rámeček) */
    g_config.main_window.shadow_stroke.offset = 0.5;
    g_config.main_window.shadow_stroke.blur = 0.8;
    g_config.main_window.shadow_stroke.alpha = 0.5;
    g_config.main_window.shadow_stroke.color = (struct color_rgba){0.0, 0.6, 0.8, 1.0};
    
    /* Widgets - default pozice z widget_registry.c */
    g_config.widgets.sysinfo = (struct widget_config){true, 20, 20, 480, 100};
    g_config.widgets.cpu     = (struct widget_config){true, 20, 140, 480, 100};
    g_config.widgets.gpu     = (struct widget_config){true, 20, 260, 480, 100};
    g_config.widgets.ram     = (struct widget_config){true, 20, 400, 480, 30};
    g_config.widgets.storage = (struct widget_config){true, 20, 460, 480, 220};
    g_config.widgets.network = (struct widget_config){true, 20, 690, 480, 160};
    g_config.widgets.clock   = (struct widget_config){true, 230, 795, 30, 30};
    
    
    /* Text defaults */
    strcpy(g_config.text.cpu_header.font_family, "Orbitron");
    g_config.text.cpu_header.font_size = 14.0;
    g_config.text.cpu_header.color = (struct color_rgba){0.7, 0.9, 1.0, 1.0};
    
    strcpy(g_config.text.cpu_usage.font_family, "Orbitron");
    g_config.text.cpu_usage.font_size = 14.0;
    g_config.text.cpu_usage.color = (struct color_rgba){0.2, 1.0, 0.2, 1.0};
    
    /* Network */
    g_config.network.auto_detect = false;
    strcpy(g_config.network.interface, "wlp13s0f3u3u2");
}

/*---------------------------------------------------------------------------------------------*/
// Parsování INI souboru
/*---------------------------------------------------------------------------------------------*/

static int parse_ini_file(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Warning: Cannot open config file: %s\n", filename);
        return -1;
    }
    
    char line[512];
    char section[128] = "";
    
    while (fgets(line, sizeof(line), f)) {
        char *trimmed = trim(line);
        
        /* Přeskočit prázdné řádky a komentáře */
        if (trimmed[0] == '\0' || trimmed[0] == '#' || trimmed[0] == ';')
            continue;
        
        /* Sekce [name] */
        if (is_section(trimmed, section, sizeof(section))) {
            continue;
        }
        
        /* Key=value */
        char key[128], value[256];
        if (!parse_keyvalue(trimmed, key, value, sizeof(value)))
            continue;
        
        /* Parsování podle sekce */
        if (strcmp(section, "surafce_window") == 0) {
            if (strcmp(key, "width") == 0)
                g_config.surface_window.width = atoi(value);
            else if (strcmp(key, "height") == 0)
                g_config.surface_window.height = atoi(value);
        }

        else if (strcmp(section, "main_window") == 0) {
            if (strcmp(key, "x") == 0)
                g_config.main_window.x = atof(value);
            else if (strcmp(key, "y") == 0)
                g_config.main_window.y = atof(value);
            else if (strcmp(key, "width") == 0)
                g_config.main_window.width = atof(value);
            else if (strcmp(key, "height") == 0)
                g_config.main_window.height = atof(value);
            else if (strcmp(key, "corner_radius") == 0)
                g_config.main_window.corner_radius = atof(value);
            else if (strcmp(key, "shadow_offset") == 0)
                g_config.main_window.shadow_offset = atof(value);
            else if (strcmp(key, "shadow_blur") == 0)
                g_config.main_window.shadow_blur = atof(value);
            else if (strcmp(key, "shadow_alpha") == 0)
                g_config.main_window.shadow_alpha = atof(value);
            else if (strcmp(key, "stroke_width") == 0)
                g_config.main_window.stroke_width = atof(value);

            // Barvy pozadí
            else if (strcmp(key, "bg_r") == 0)
                g_config.main_window.bg_color.r = atof(value);
            else if (strcmp(key, "bg_g") == 0)
                g_config.main_window.bg_color.g = atof(value);
            else if (strcmp(key, "bg_b") == 0)
                g_config.main_window.bg_color.b = atof(value);
            else if (strcmp(key, "bg_a") == 0)
                g_config.main_window.bg_color.a = atof(value);

            // Barvy rámečku
            else if (strcmp(key, "stroke_r") == 0)
                g_config.main_window.stroke_color.r = atof(value);
            else if (strcmp(key, "stroke_g") == 0)
                g_config.main_window.stroke_color.g = atof(value);
            else if (strcmp(key, "stroke_b") == 0)
                g_config.main_window.stroke_color.b = atof(value);
            else if (strcmp(key, "stroke_a") == 0)
                g_config.main_window.stroke_color.a = atof(value);

            // Barvy stínu
            else if (strcmp(key, "shadow_r") == 0)
                g_config.main_window.shadow_color.r = atof(value);
            else if (strcmp(key, "shadow_g") == 0)
                g_config.main_window.shadow_color.g = atof(value);
            else if (strcmp(key, "shadow_b") == 0)
                g_config.main_window.shadow_color.b = atof(value);
            else if (strcmp(key, "shadow_a") == 0)
                g_config.main_window.shadow_color.a = atof(value);

            // Shadow fill
            else if (strcmp(key, "shadow_fill_offset") == 0)
                g_config.main_window.shadow_fill.offset = atof(value);
            else if (strcmp(key, "shadow_fill_blur") == 0)
                g_config.main_window.shadow_fill.blur = atof(value);
            else if (strcmp(key, "shadow_fill_alpha") == 0)
                g_config.main_window.shadow_fill.alpha = atof(value);
            else if (strcmp(key, "shadow_fill_r") == 0)
                g_config.main_window.shadow_fill.color.r = atof(value);
            else if (strcmp(key, "shadow_fill_g") == 0)
                g_config.main_window.shadow_fill.color.g = atof(value);
            else if (strcmp(key, "shadow_fill_b") == 0)
                g_config.main_window.shadow_fill.color.b = atof(value);
            else if (strcmp(key, "shadow_fill_a") == 0)
                g_config.main_window.shadow_fill.color.a = atof(value);

            // Shadow stroke
            else if (strcmp(key, "shadow_stroke_offset") == 0)
                g_config.main_window.shadow_stroke.offset = atof(value);
            else if (strcmp(key, "shadow_stroke_blur") == 0)
                g_config.main_window.shadow_stroke.blur = atof(value);
            else if (strcmp(key, "shadow_stroke_alpha") == 0)
                g_config.main_window.shadow_stroke.alpha = atof(value);
            else if (strcmp(key, "shadow_stroke_r") == 0)
                g_config.main_window.shadow_stroke.color.r = atof(value);
            else if (strcmp(key, "shadow_stroke_g") == 0)
                g_config.main_window.shadow_stroke.color.g = atof(value);
            else if (strcmp(key, "shadow_stroke_b") == 0)
                g_config.main_window.shadow_stroke.color.b = atof(value);
            else if (strcmp(key, "shadow_stroke_a") == 0)
                g_config.main_window.shadow_stroke.color.a = atof(value);

        }

        else if (strcmp(section, "widget.sysinfo") == 0) {
            if (strcmp(key, "enabled") == 0)
                g_config.widgets.sysinfo.enabled = (strcmp(value, "true") == 0);
            else if (strcmp(key, "x") == 0)
                g_config.widgets.sysinfo.x = atof(value);
            else if (strcmp(key, "y") == 0)
                g_config.widgets.sysinfo.y = atof(value);
            else if (strcmp(key, "width") == 0)
                g_config.widgets.sysinfo.width = atof(value);
            else if (strcmp(key, "height") == 0)
                g_config.widgets.sysinfo.height = atof(value);
        }
        else if (strcmp(section, "widget.cpu") == 0) {
            if (strcmp(key, "enabled") == 0)
                g_config.widgets.cpu.enabled = (strcmp(value, "true") == 0);
            else if (strcmp(key, "x") == 0)
                g_config.widgets.cpu.x = atof(value);
            else if (strcmp(key, "y") == 0)
                g_config.widgets.cpu.y = atof(value);
            else if (strcmp(key, "width") == 0)
                g_config.widgets.cpu.width = atof(value);
            else if (strcmp(key, "height") == 0)
                g_config.widgets.cpu.height = atof(value);
        }
        else if (strcmp(section, "widget.gpu") == 0) {
            if (strcmp(key, "enabled") == 0)
                g_config.widgets.gpu.enabled = (strcmp(value, "true") == 0);
            else if (strcmp(key, "x") == 0)
                g_config.widgets.gpu.x = atof(value);
            else if (strcmp(key, "y") == 0)
                g_config.widgets.gpu.y = atof(value);
            else if (strcmp(key, "width") == 0)
                g_config.widgets.gpu.width = atof(value);
            else if (strcmp(key, "height") == 0)
                g_config.widgets.gpu.height = atof(value);
        }
        else if (strcmp(section, "widget.ram") == 0) {
            if (strcmp(key, "enabled") == 0)
                g_config.widgets.ram.enabled = (strcmp(value, "true") == 0);
            else if (strcmp(key, "x") == 0)
                g_config.widgets.ram.x = atof(value);
            else if (strcmp(key, "y") == 0)
                g_config.widgets.ram.y = atof(value);
            else if (strcmp(key, "width") == 0)
                g_config.widgets.ram.width = atof(value);
            else if (strcmp(key, "height") == 0)
                g_config.widgets.ram.height = atof(value);
        }
        else if (strcmp(section, "widget.storage") == 0) {
            if (strcmp(key, "enabled") == 0)
                g_config.widgets.storage.enabled = (strcmp(value, "true") == 0);
            else if (strcmp(key, "x") == 0)
                g_config.widgets.storage.x = atof(value);
            else if (strcmp(key, "y") == 0)
                g_config.widgets.storage.y = atof(value);
            else if (strcmp(key, "width") == 0)
                g_config.widgets.storage.width = atof(value);
            else if (strcmp(key, "height") == 0)
                g_config.widgets.storage.height = atof(value);
        }
        else if (strcmp(section, "widget.network") == 0) {
            if (strcmp(key, "enabled") == 0)
                g_config.widgets.network.enabled = (strcmp(value, "true") == 0);
            else if (strcmp(key, "x") == 0)
                g_config.widgets.network.x = atof(value);
            else if (strcmp(key, "y") == 0)
                g_config.widgets.network.y = atof(value);
            else if (strcmp(key, "width") == 0)
                g_config.widgets.network.width = atof(value);
            else if (strcmp(key, "height") == 0)
                g_config.widgets.network.height = atof(value);
        }
        else if (strcmp(section, "widget.clock") == 0) {
            if (strcmp(key, "enabled") == 0)
                g_config.widgets.clock.enabled = (strcmp(value, "true") == 0);
            else if (strcmp(key, "x") == 0)
                g_config.widgets.clock.x = atof(value);
            else if (strcmp(key, "y") == 0)
                g_config.widgets.clock.y = atof(value);
            else if (strcmp(key, "width") == 0)
                g_config.widgets.clock.width = atof(value);
            else if (strcmp(key, "height") == 0)
                g_config.widgets.clock.height = atof(value);
        }
        else if (strcmp(section, "network") == 0) {
            if (strcmp(key, "auto_detect") == 0)
                g_config.network.auto_detect = (strcmp(value, "true") == 0);
            else if (strcmp(key, "interface") == 0)
                strncpy(g_config.network.interface, value, sizeof(g_config.network.interface) - 1);
        }
        /* Další sekce můžeš přidat podle potřeby */
    }
    
    fclose(f);
    return 0;
}

/*---------------------------------------------------------------------------------------------*/
// Public API
/*---------------------------------------------------------------------------------------------*/

int config_load_all(void)
{
    /* Nejdřív nastav defaults */
    config_set_defaults();
    
    /* Pak načti INI (přepíše defaults) */
    int ret = parse_ini_file("config/config.ini");
    
    if (ret != 0) {
        fprintf(stderr, "Config: Using defaults (config.ini not found or invalid)\n");
    } else {
        printf("Config: Loaded successfully from config/config.ini\n");
    }
    
    return 0; /* Vždy vrátí success (používá defaults jako fallback) */
}

int config_save_all(void)
{
    /* TODO: Implementovat ukládání zpět do INI */
    fprintf(stderr, "Config saving not yet implemented\n");
    return -1;
}

void config_print_debug(void)
{
    printf("=== CONFIG DEBUG ===\n");
    printf("Surface Window: %dx%d\n", g_config.surface_window.width, g_config.surface_window.height);
    printf("Widgets:\n");
    printf("  sysinfo: enabled=%d pos=(%.0f,%.0f) size=(%.0fx%.0f)\n",
           g_config.widgets.sysinfo.enabled,
           g_config.widgets.sysinfo.x, g_config.widgets.sysinfo.y,
           g_config.widgets.sysinfo.width, g_config.widgets.sysinfo.height);
    printf("  cpu: enabled=%d pos=(%.0f,%.0f)\n",
           g_config.widgets.cpu.enabled,
           g_config.widgets.cpu.x, g_config.widgets.cpu.y);
    printf("Network: interface=%s (auto=%d)\n",
           g_config.network.interface, g_config.network.auto_detect);
    printf("====================\n");
}
