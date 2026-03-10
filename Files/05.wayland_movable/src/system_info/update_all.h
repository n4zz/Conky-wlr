#pragma once

void update_all_stats(struct cpu_stat *cpu,
                      struct gpu_stat *gpu,
                      struct ram_stat *ram,
                      struct disk_stat *disk_home,
                      struct disk_stat *disk_root,
                      struct network_stat *net,
                      struct network_stat *ip);
