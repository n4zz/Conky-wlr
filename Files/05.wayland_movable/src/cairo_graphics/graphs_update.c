#include "graphs_update.h"

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
                       const struct network_stat *net)
{
    history_graph_push(cpu_graph, cpu->usage);
    history_graph_push(gpu_graph, gpu->utilization_percent);
    history_graph_push(ram_graph, ram->percent);

    history_graph_push(disk_read_graph, disk_home->read_speed_kbps);
    history_graph_push(disk_write_graph, disk_home->write_speed_kbps);

    history_graph_push(net_rx_graph, net->rx_speed_kbps);
    history_graph_push(net_tx_graph, net->tx_speed_kbps);
}
