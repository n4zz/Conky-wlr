#include "ram_monitor.h"
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------------------------*/
//     RAM
/*---------------------------------------------------------------------------------------------*/

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

    if (ram->total_kb > 0) {
        ram->percent = ((double)ram->used_kb / (double)ram->total_kb) * 100.0;
    } else {
        ram->percent = 0.0;
    }
}
