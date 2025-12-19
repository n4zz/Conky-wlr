#include "system_variables.h"
#include <stdio.h>
#include <string.h>

/*     CPU     */
void cpu_init(struct cpu_stat *cpu)
{
    cpu->prev_total = 0;
    cpu->prev_idle = 0;
    cpu->usage = 0.0;

    cpu_update(cpu); /* naplní prev hodnoty */
}

void cpu_update(struct cpu_stat *cpu)
{
    FILE *f = fopen("/proc/stat", "r");
    if (!f) return;

    char line[256];
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        return;
    }
    fclose(f);

    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle,
           &iowait, &irq, &softirq, &steal);

    unsigned long long idle_now = idle + iowait;
    unsigned long long total_now =
        user + nice + system + idle + iowait + irq + softirq + steal;

    if (cpu->prev_total != 0) {
        unsigned long long total_diff = total_now - cpu->prev_total;
        unsigned long long idle_diff  = idle_now  - cpu->prev_idle;

        if (total_diff > 0) {
            cpu->usage = 100.0 *
                (double)(total_diff - idle_diff) /
                (double)total_diff;
        }
    }

    cpu->prev_total = total_now;
    cpu->prev_idle  = idle_now;
}

/*     RAM    */
void ram_update(struct ram_stat *ram) {
    FILE *f = fopen("/proc/meminfo", "r");
    if (!f) return;

    char key[64];
    unsigned long value;
    char unit[16];

    memset(ram, 0, sizeof(*ram));

    while (fscanf(f, "%63s %lu %15s\n", key, &value, unit) == 3) {
        if (strcmp(key, "MemTotal:") == 0)
            ram->total_kb = value;
        else if (strcmp(key, "MemFree:") == 0)
            ram->free_kb = value;
        else if (strcmp(key, "MemAvailable:") == 0)
            ram->available_kb = value;
    }

    fclose(f);

    if (ram->total_kb > ram->available_kb)
        ram->used_kb = ram->total_kb - ram->available_kb;
}
