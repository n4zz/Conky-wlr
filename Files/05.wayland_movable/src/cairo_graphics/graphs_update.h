#pragma once

#include "history_graph.h"
#include "../system_info/cpu_monitor.h"
#include "../system_info/gpu_monitor.h"
#include "../system_info/ram_monitor.h"
#include "../system_info/network_monitor.h"
#include "../system_info/storage_monitor.h"

void update_all_graphs(struct history_graph *cpu_graph,
                       struct history_graph *gpu_graph,
                       struct history_graph *ram_graph,
                       struct history_graph *disk_read_graph,
                       struct history_graph *disk_write_graph,
                       struct history_graph *net_rx_graph,
                       struct history_graph *net_tx_graph,
                       const struct cpu_stat *cpu,
                       const struct gpu_stat *gpu,
                       const struct ram_stat *ram,
                       const struct disk_stat *disk_home,
                       const struct network_stat *net);

