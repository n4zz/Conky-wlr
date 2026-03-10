#include "graphs_cleanup.h"

void cleanup_all_graphs(struct history_graph *cpu_graph,
                        struct history_graph *gpu_graph,
                        struct history_graph *ram_graph,
                        struct history_graph *disk_read_graph,
                        struct history_graph *disk_write_graph,
                        struct history_graph *net_rx_graph,
                        struct history_graph *net_tx_graph)
{
    history_graph_destroy(cpu_graph);
    history_graph_destroy(gpu_graph);
    history_graph_destroy(ram_graph);
    history_graph_destroy(disk_read_graph);
    history_graph_destroy(disk_write_graph);
    history_graph_destroy(net_rx_graph);
    history_graph_destroy(net_tx_graph);
}
