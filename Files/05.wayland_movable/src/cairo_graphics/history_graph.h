/* ==========================================
 * history_graph.h - Generic History Graph Module
 * ========================================== */

#ifndef HISTORY_GRAPH_H
#define HISTORY_GRAPH_H

#include <cairo/cairo.h>
#include <math.h>

/*
 * Struktura pro univerzální historický graf
 * Může zobrazit CPU, RAM, network, disk I/O, teplotu, cokoliv!
 */
struct history_graph {
    double *history;      /* pole historických hodnot */
    int capacity;         /* maximální počet vzorků */
    int count;            /* aktuální počet vzorků */
    int head;             /* index nejnovějšího vzorku (kruhový buffer) */
    
    /* Rozsah hodnot -----------------------------------------------------------------*/
    double min_value;     /* minimální hodnota (např. 0.0) */
    double max_value;     /* maximální hodnota (např. 100.0) */
    

    /* Popisek (volitelné) -----------------------------------------------------------*/
    char *label;          /* např. "CPU %", "RAM", "Network KB/s" */
    

    /* Barva rámečku (volitelné customizace) -----------------------------------------*/
    struct {
        double r, g, b, a;
    } frame_color;

    /* síla čáry rámečku -------------------------------------------------------------*/
    double frame_line_width;


    /* Barva mřížky (volitelné customizace) ------------------------------------------*/
    struct {
        double r, g, b, a;
    } grid_color;

    /* síla čáry mřížky --------------------------------------------------------------*/
    double grid_line_width;


    /* Barvy (volitelné customizace) -------------------------------------------------*/
    struct {
        double r, g, b, a;
    } line_color;         /* barva křivky */
    
    struct {
        double top_r, top_g, top_b, top_a;     /* barva nahoře */
        double bot_r, bot_g, bot_b, bot_a;     /* barva dole */
    } fill_gradient;

    struct {
        double r, g, b, a;                     /* barva pozadí*/

    } fill_bg;


    /* ------------------------------------------------------------------------------- */
    int show_grid;                            /* mřížka  off = 0 , on =1 */
    int show_frame;                           /* rámeček off = 0 , on =1 */
    int show_background;                      /* pozadí  off = 0 , on =1 */
};

/*
 * Inicializuje historický graf
 * 
 * capacity  - počet vzorků v historii (např. 60 = 1 minuta při 1s ticku)
 * min_value - minimální hodnota osy Y (např. 0.0)
 * max_value - maximální hodnota osy Y (např. 100.0)
 * label     - popisek grafu (může být NULL)
 */
void history_graph_init(struct history_graph *graph,
                        int capacity,
                        double min_value,
                        double max_value,
                        const char *label
                        );

/*
 * Přidá nový vzorek do historie
 * Hodnota je automaticky ořeznuta do rozsahu min_value - max_value
 */
void history_graph_push(struct history_graph *graph, double value);

/*
 * Vykreslí historický graf
 * 
 * cr          - Cairo context
 * graph       - graf k vykreslení
 * x, y        - levý horní roh
 * width       - šířka grafu
 * height      - výška grafu
 * show_grid   - 1 = zobrazit mřížku, 0 = bez mřížky
 * show_label  - 1 = zobrazit popisek, 0 = bez popisku
 */
void history_graph_draw(cairo_t *cr,
                        struct history_graph *graph,
                        double x, double y,
                        double width, double height,
                        int show_frame,
                        int show_grid,
                        int show_label,
                        int show_background
                        );

/*
 * Nastaví vlastní barvu křivky
 */
void history_graph_set_line_color(struct history_graph *graph,
                                   double r, double g, double b, double a);

/*
 * Nastaví vlastní gradient výplně (od vrcholu k základně)
 */
void history_graph_set_fill_gradient(struct history_graph *graph,
                                      double top_r, double top_g, double top_b, double top_a,
                                      double bot_r, double bot_g, double bot_b, double bot_a);

/*
 * Uvolní paměť grafu
 */
void history_graph_destroy(struct history_graph *graph);

#endif /* HISTORY_GRAPH_H */

