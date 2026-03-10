#pragma once

#include "cpu_monitor.h"
#include "gpu_monitor.h"
#include "ram_monitor.h"
#include "network_monitor.h"
#include "storage_monitor.h"
#include "system_info_static.h"

void init_all_stats(struct system_info_static *sys_info,
                    struct cpu_stat *cpu,
                    struct gpu_stat *gpu,
                    struct ram_stat *ram,
                    struct disk_stat *disk_home,
                    struct disk_stat *disk_root,
                    struct network_stat *net,
                    struct network_stat *ip);
