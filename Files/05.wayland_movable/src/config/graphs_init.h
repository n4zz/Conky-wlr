#pragma once

#include "../cairo_graphics/history_graph.h"

void init_all_graphs(struct history_graph *cpu_graph,
                     struct history_graph *gpu_graph,
                     struct history_graph *ram_graph,
                     struct history_graph *disk_read_graph,
                     struct history_graph *disk_write_graph,
                     struct history_graph *net_rx_graph,
                     struct history_graph *net_tx_graph);
