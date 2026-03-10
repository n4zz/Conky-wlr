#ifndef UI_CONTEXT_H
#define UI_CONTEXT_H

#include "../system_info/cpu_monitor.h"
#include "../system_info/ram_monitor.h"
#include "../system_info/network_monitor.h"
#include "../system_info/storage_monitor.h"
#include "../system_info/gpu_monitor.h"
#include "../system_info/system_info_static.h"

#include "../cairo_graphics/history_graph.h"

struct ui_context {
    struct system_info_static *sys_info;

    struct cpu_stat *cpu;
    struct gpu_stat *gpu;
    struct ram_stat *ram;

    struct disk_stat *disk_home;
    struct disk_stat *disk_root;

    struct network_stat *net;
    struct network_stat *ip;

    struct history_graph *cpu_graph;
    struct history_graph *gpu_graph;
    struct history_graph *ram_graph;
    struct history_graph *disk_read_graph;
    struct history_graph *disk_write_graph;
    struct history_graph *net_rx_graph;
    struct history_graph *net_tx_graph;
};

#endif
