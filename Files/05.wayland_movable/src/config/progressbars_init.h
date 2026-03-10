#pragma once

#include "../cairo_graphics/circle_bar.h"
#include "../cairo_graphics/led_circle_bar.h"
#include "../cairo_graphics/gauge_bar.h"
#include "../cairo_graphics/hexagon_progress.h"
#include "../cairo_graphics/horizontal_bar.h"
#include "../cairo_graphics/vertical_bar.h"

/*------------------------------------------------------------------------*/
/* C I R C L E  - PROGRESS BAR */
/*------------------------------------------------------------------------*/
extern circle_bar_t circle_bar_cpu;
extern circle_bar_t circle_bar_gpu;
extern circle_bar_t circle_bar_ram;
extern circle_bar_t circle_bar_disk;
extern circle_bar_t circle_bar_network;


/*------------------------------------------------------------------------*/
/* L E D   C I R C L E - PROGRESS BAR */
/*------------------------------------------------------------------------*/
extern led_circle_bar_t led_circle_bar_cpu;
extern led_circle_bar_t led_circle_bar_gpu;
extern led_circle_bar_t led_circle_bar_ram;
extern led_circle_bar_t led_circle_bar_disk;
extern led_circle_bar_t led_circle_bar_network;


/*------------------------------------------------------------------------*/
/* G A U G E - PROGRESS BAR */
/*------------------------------------------------------------------------*/
extern gauge_bar_t gauge_bar_cpu;
extern gauge_bar_t gauge_bar_gpu;
extern gauge_bar_t gauge_bar_ram;
extern gauge_bar_t gauge_bar_disk;
extern gauge_bar_t gauge_bar_network;


/*------------------------------------------------------------------------*/
/* H E X A G O N - PROGRESS BAR */
/*------------------------------------------------------------------------*/
extern hexagon_bar_t hexagon_bar_cpu;
extern labels_t labels_cpu;
extern hexagon_bar_t hexagon_bar_gpu;
extern labels_t labels_gpu;
extern hexagon_bar_t hexagon_bar_ram;
extern labels_t labels_ram;
extern hexagon_bar_t hexagon_bar_disk;
extern labels_t labels_disk;
extern hexagon_bar_t hexagon_bar_network;
extern labels_t labels_network;

/*------------------------------------------------------------------------*/
/* H O R I Z O N T A L  - PROGRESS BAR */
/*------------------------------------------------------------------------*/
extern horizontal_bar_t horizontal_bar_cpu;
extern horizontal_bar_t horizontal_bar_gpu;
extern horizontal_bar_t horizontal_bar_ram;
extern horizontal_bar_t horizontal_bar_disk;
extern horizontal_bar_t horizontal_bar_network;


/*------------------------------------------------------------------------*/
/* V E R T I C A L  - PROGRESS BAR */
/*------------------------------------------------------------------------*/
extern vertical_bar_t vertical_bar_cpu;
extern vertical_bar_t vertical_bar_gpu;
extern vertical_bar_t vertical_bar_ram;
extern vertical_bar_t vertical_bar_disk;
extern vertical_bar_t vertical_bar_network;
