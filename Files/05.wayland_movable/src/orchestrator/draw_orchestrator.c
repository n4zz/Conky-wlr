#include "draw_orchestrator.h"
#include "../config/config_loader.h"
//#include "../config/config_types.h"
#include "../widgets/widget_registry.h"

#include "../system_info/cpu_monitor.h"
#include "../system_info/gpu_monitor.h"
#include "../system_info/ram_monitor.h"
#include "../system_info/network_monitor.h"
#include "../system_info/storage_monitor.h"
#include "../system_info/system_info_static.h"
#include "../system_info/init_all.h"
#include "../system_info/update_all.h"

#include "../cairo_graphics/history_graph.h"
#include "../config/graphs_init.h"
#include "../cairo_graphics/graphs_update.h"
#include "../cairo_graphics/graphs_cleanup.h"

#include "../ui/ui_context.h"

#include "../widgets/draw_all.h"

#include <stdbool.h>

/* ---------------------------------------------------------
   SHARED STATE (visible to both draw and cleanup)
   --------------------------------------------------------- */

static bool initialized = false;

// --- SYSTEM DATA ---
static struct system_info_static sys_info;
static struct cpu_stat cpu;
static struct gpu_stat gpu;
static struct ram_stat ram;
static struct disk_stat disk_home;
static struct disk_stat disk_root;
static struct network_stat net;
static struct network_stat ip;

// --- GRAPHS ---
static struct history_graph cpu_graph;
static struct history_graph gpu_graph;
static struct history_graph ram_graph;
static struct history_graph disk_read_graph;
static struct history_graph disk_write_graph;
static struct history_graph net_rx_graph;
static struct history_graph net_tx_graph;

/* ---------------------------------------------------------
   DRAW
   --------------------------------------------------------- */

void draw_orchestrator(cairo_t *cr)
{
    if (!initialized) {

        config_load_all();         // Načíst config
        widget_registry_apply_config();
        config_print_debug();      // Debug výpis (můžeš smazat později)

        system_info_static_init(&sys_info);

        init_all_stats(&sys_info, &cpu, &gpu, &ram,
                       &disk_home, &disk_root,
                       &net, &ip);

        init_all_graphs(&cpu_graph, &gpu_graph, &ram_graph,
                        &disk_read_graph, &disk_write_graph,
                        &net_rx_graph, &net_tx_graph);

        initialized = true;
    }

    update_all_stats(&cpu, &gpu, &ram, &disk_home, &disk_root, &net, &ip);

    update_all_graphs(&cpu_graph, &gpu_graph, &ram_graph,
                      &disk_read_graph, &disk_write_graph,
                      &net_rx_graph, &net_tx_graph,
                      &cpu, &gpu, &ram, &disk_home, &net);

    struct ui_context ctx = {
        .sys_info = &sys_info,
        .cpu = &cpu,
        .gpu = &gpu,
        .ram = &ram,
        .disk_home = &disk_home,
        .disk_root = &disk_root,
        .net = &net,
        .ip = &ip,
        .cpu_graph = &cpu_graph,
        .gpu_graph = &gpu_graph,
        .ram_graph = &ram_graph,
        .disk_read_graph = &disk_read_graph,
        .disk_write_graph = &disk_write_graph,
        .net_rx_graph = &net_rx_graph,
        .net_tx_graph = &net_tx_graph
    };
    draw_all_widgets(cr, &ctx);
}

/* ---------------------------------------------------------
   CLEANUP
   --------------------------------------------------------- */

void cleanup_orchestrator(void)
{
    cleanup_all_graphs(&cpu_graph, &gpu_graph, &ram_graph,
                       &disk_read_graph, &disk_write_graph,
                       &net_rx_graph, &net_tx_graph);
}
