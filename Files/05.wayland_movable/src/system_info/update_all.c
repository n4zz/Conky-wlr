#include "cpu_monitor.h"
#include "gpu_monitor.h"
#include "ram_monitor.h"
#include "network_monitor.h"
#include "storage_monitor.h"

void update_all_stats(struct cpu_stat *cpu,
                      struct gpu_stat *gpu,
                      struct ram_stat *ram,
                      struct disk_stat *disk_home,
                      struct disk_stat *disk_root,
                      struct network_stat *net,
                      struct network_stat *ip)
{
    cpu_update(cpu);
    cpu_get_frequency(cpu);
    cpu_get_temperature(cpu);

    gpu_update(gpu);
    ram_update(ram);

    disk_update(disk_home);
    disk_update(disk_root);

    network_update(net);

    static int ip_tick = 0;
    if (++ip_tick >= 5) {
        ip_update(ip);
        ip_tick = 0;
    }
}
