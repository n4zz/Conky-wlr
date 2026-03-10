#include "graphs_init.h"

/*########################################################################*/
/////                   G R A P H S     T H E M E S                    /////
/*########################################################################*/

void init_all_graphs(struct history_graph *cpu_graph,
                     struct history_graph *gpu_graph,
                     struct history_graph *ram_graph,
                     struct history_graph *disk_read_graph,
                     struct history_graph *disk_write_graph,
                     struct history_graph *net_rx_graph,
                     struct history_graph *net_tx_graph)
{

/*------------------------------------------------------------------------*/
    /* C P U   G R A P H  - green */
/*------------------------------------------------------------------------*/
    history_graph_init(cpu_graph, 60, 0.0, 100.0, "CPU GRAPH");
    history_graph_set_line_color(cpu_graph, 0.2, 1.0, 0.2, 1.0);
    history_graph_set_fill_gradient(cpu_graph,
                                    0.2, 0.8, 0.2, 0.6,
                                    0.1, 0.5, 0.2, 0.2);
    /* Custom rámečku */
    cpu_graph->show_frame = 1;               // on/of
    cpu_graph->frame_line_width = 0.8;       //  síla čáry
    cpu_graph->frame_color.r = 0.5;
    cpu_graph->frame_color.g = 0.5;
    cpu_graph->frame_color.b = 0.5;
    cpu_graph->frame_color.a = 0.8;

    /* Custom mřížky */
    cpu_graph->show_grid = 1;                // on/of
    cpu_graph->grid_line_width  = 0.5;       //  síla čáry
    cpu_graph->grid_color.r = 0.5;
    cpu_graph->grid_color.g = 0.5;
    cpu_graph->grid_color.b = 0.5;
    cpu_graph->grid_color.a = 0.8;

    /* Výchozí pozadí */
    cpu_graph->show_background = 1;
    cpu_graph->fill_bg.r = 0.1;
    cpu_graph->fill_bg.g = 0.3;
    cpu_graph->fill_bg.b = 0.1;
    cpu_graph->fill_bg.a = 0.3;

/*------------------------------------------------------------------------*/
    /* G P U   G R A P H  - blue  */
/*------------------------------------------------------------------------*/
    history_graph_init(gpu_graph, 60, 0.0, 100.0, "GPU GRAPH");
    history_graph_set_line_color(gpu_graph, 0.2, 0.6, 1.0, 1.0);
    history_graph_set_fill_gradient(gpu_graph,
                                    0.2, 0.6, 1.0, 0.6,
                                    0.1, 0.2, 0.5, 0.2);
   /* Custom rámečku */
    gpu_graph->show_frame = 1;                // on/of
    gpu_graph->frame_line_width = 0.8;       //  síla čáry
    gpu_graph->frame_color.r = 0.5;
    gpu_graph->frame_color.g = 0.5;
    gpu_graph->frame_color.b = 0.5;
    gpu_graph->frame_color.a = 0.8;

    /* Custom mřížky */
    gpu_graph->show_grid = 1;                // on/of
    gpu_graph->grid_line_width  = 0.5;       //  síla čáry
    gpu_graph->grid_color.r = 0.5;
    gpu_graph->grid_color.g = 0.5;
    gpu_graph->grid_color.b = 0.5;
    gpu_graph->grid_color.a = 0.8;

    /* Výchozí pozadí */
    gpu_graph->show_background = 1;
    gpu_graph->fill_bg.r = 0.0;
    gpu_graph->fill_bg.g = 0.1;
    gpu_graph->fill_bg.b = 0.3;
    gpu_graph->fill_bg.a = 0.3;

/*------------------------------------------------------------------------*/
    /* R A M  G R A P H           */
/*------------------------------------------------------------------------*/
    history_graph_init(ram_graph, 60, 0.0, 100.0, "RAM GRAPH");
    history_graph_set_line_color(ram_graph, 0.2, 0.6, 1.0, 1.0);
    history_graph_set_fill_gradient(ram_graph,
                                    0.2, 0.6, 1.0, 0.6,
                                    0.1, 0.2, 0.5, 0.2);
    /* Custom rámečku */
    ram_graph->show_frame = 1;                // on/of
    ram_graph->frame_line_width = 0.8;       //  síla čáry
    ram_graph->frame_color.r = 0.5;
    ram_graph->frame_color.g = 0.5;
    ram_graph->frame_color.b = 0.5;
    ram_graph->frame_color.a = 0.8;

    /* Custom mřížky */
    ram_graph->show_grid = 1;                // on/of
    ram_graph->grid_line_width  = 0.5;       //  síla čáry
    ram_graph->grid_color.r = 0.5;
    ram_graph->grid_color.g = 0.5;
    ram_graph->grid_color.b = 0.5;
    ram_graph->grid_color.a = 0.8;

    /* Výchozí pozadí */
    ram_graph->show_background = 1;
    ram_graph->fill_bg.r = 0.1;
    ram_graph->fill_bg.g = 0.1;
    ram_graph->fill_bg.b = 0.1;
    ram_graph->fill_bg.a = 0.8;

/*------------------------------------------------------------------------*/
    /* D I S K   R E A D   G R A F */
/*------------------------------------------------------------------------*/
    history_graph_init(disk_read_graph, 60, 0.0, 100.0, "DISK READ");
    history_graph_set_line_color(disk_read_graph, 0.2, 1.0, 0.7, 1.0);
    history_graph_set_fill_gradient(disk_read_graph,
                                    0.2, 1.0, 0.7, 0.6,
                                    0.1, 0.5, 0.4, 0.2);
    /* Custom rámečku */
    disk_read_graph->show_frame = 1;                // on/of
    disk_read_graph->frame_line_width = 1.0;       //  síla čáry
    disk_read_graph->frame_color.r = 0.5;
    disk_read_graph->frame_color.g = 0.5;
    disk_read_graph->frame_color.b = 0.5;
    disk_read_graph->frame_color.a = 0.7;

    /* Custom mřížky */
    disk_read_graph->show_grid = 1;                // on/of
    disk_read_graph->grid_line_width  = 0.5;       //  síla čáry
    disk_read_graph->grid_color.r = 0.5;
    disk_read_graph->grid_color.g = 0.5;
    disk_read_graph->grid_color.b = 0.5;
    disk_read_graph->grid_color.a = 0.5;

    /* Výchozí pozadí */
    disk_read_graph->show_background = 1;
    disk_read_graph->fill_bg.r = 0.1;
    disk_read_graph->fill_bg.g = 0.1;
    disk_read_graph->fill_bg.b = 0.1;
    disk_read_graph->fill_bg.a = 0.8;

/*------------------------------------------------------------------------*/
    /* D I S K   W R I T E   G R A F */
/*------------------------------------------------------------------------*/
    history_graph_init(disk_write_graph, 60, 0.0, 100.0, "DISK WRITE");
    history_graph_set_line_color(disk_write_graph, 1.0, 0.5, 0.3, 1.0);
    history_graph_set_fill_gradient(disk_write_graph,
                                    1.0, 0.5, 0.3, 0.6,
                                    0.5, 0.2, 0.1, 0.2);
    /* Custom rámečku */
    disk_write_graph->show_frame = 1;                // on/of
    disk_write_graph->frame_line_width = 1.0;       //  síla čáry
    disk_write_graph->frame_color.r = 0.5;
    disk_write_graph->frame_color.g = 0.5;
    disk_write_graph->frame_color.b = 0.5;
    disk_write_graph->frame_color.a = 0.7;

    /* Custom mřížky */
    disk_write_graph->show_grid = 1;                // on/of
    disk_write_graph->grid_line_width  = 0.5;       //  síla čáry
    disk_write_graph->grid_color.r = 0.5;
    disk_write_graph->grid_color.g = 0.5;
    disk_write_graph->grid_color.b = 0.5;
    disk_write_graph->grid_color.a = 0.5;

    /* Výchozí pozadí */
    disk_write_graph->show_background = 1;
    disk_write_graph->fill_bg.r = 0.1;
    disk_write_graph->fill_bg.g = 0.1;
    disk_write_graph->fill_bg.b = 0.1;
    disk_write_graph->fill_bg.a = 0.8;

/*------------------------------------------------------------------------*/
    /* N E T W O R K   RX   G R A F (download) */
/*------------------------------------------------------------------------*/
    history_graph_init(net_rx_graph, 60, 0.0, 1024.0, "NET RX");
    history_graph_set_line_color(net_rx_graph, 0.2, 1.0, 0.7, 1.0);
    history_graph_set_fill_gradient(net_rx_graph,
                                    0.2, 1.0, 0.7, 0.6,
                                    0.1, 0.5, 0.4, 0.2);
    /* Customrámečku */
    net_rx_graph->show_frame = 1;                // on/of
    net_rx_graph->frame_line_width = 0.8;       //  síla čáry
    net_rx_graph->frame_color.r = 0.5;
    net_rx_graph->frame_color.g = 0.5;
    net_rx_graph->frame_color.b = 0.5;
    net_rx_graph->frame_color.a = 0.3;

    /* Custom mřížky */
    net_rx_graph->show_grid = 1;                // on/of
    net_rx_graph->grid_line_width  = 0.5;       //  síla čáry
    net_rx_graph->grid_color.r = 0.3;
    net_rx_graph->grid_color.g = 0.3;
    net_rx_graph->grid_color.b = 0.3;
    net_rx_graph->grid_color.a = 0.5;

    /* Výchozí pozadí */
    net_rx_graph->show_background = 1;
    net_rx_graph->fill_bg.r = 0.1;
    net_rx_graph->fill_bg.g = 0.3;
    net_rx_graph->fill_bg.b = 0.1;
    net_rx_graph->fill_bg.a = 0.3;

/*------------------------------------------------------------------------*/
    /* N E T W O R K   TX   G R A F (upload) */
/*------------------------------------------------------------------------*/
    history_graph_init(net_tx_graph, 60, 0.0, 1024.0, "NET TX");
    history_graph_set_line_color(net_tx_graph, 1.0, 0.5, 0.3, 1.0);
    history_graph_set_fill_gradient(net_tx_graph,
                                    1.0, 0.5, 0.3, 0.6,
                                    0.5, 0.2, 0.1, 0.2);
    /* Customrámečku */
    net_tx_graph->show_frame = 1;                // on/of
    net_tx_graph->frame_line_width = 0.8;       //  síla čáry
    net_tx_graph->frame_color.r = 0.5;
    net_tx_graph->frame_color.g = 0.5;
    net_tx_graph->frame_color.b = 0.5;
    net_tx_graph->frame_color.a = 0.3;

    /* Custom mřížky */
    net_tx_graph->show_grid = 1;                // on/of
    net_tx_graph->grid_line_width  = 0.5;       //  síla čáry
    net_tx_graph->grid_color.r = 0.3;
    net_tx_graph->grid_color.g = 0.3;
    net_tx_graph->grid_color.b = 0.3;
    net_tx_graph->grid_color.a = 0.5;

    /* Výchozí pozadí */
    net_tx_graph->show_background = 1;
    net_tx_graph->fill_bg.r = 0.4;
    net_tx_graph->fill_bg.g = 0.1;
    net_tx_graph->fill_bg.b = 0.1;
    net_tx_graph->fill_bg.a = 0.3;
}
