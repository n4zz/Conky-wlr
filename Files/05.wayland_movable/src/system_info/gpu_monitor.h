/* gpu_monitor.h
 *
 * NVIDIA GPU monitoring (usage, temperature, VRAM, frequency, etc.)
 * ČISTĚ logika čtení/výpočtu – žádné vykreslování.
 */

#ifndef GPU_MONITOR_H
#define GPU_MONITOR_H

#include <stdbool.h>

/* Jednoduchá struktura pro jednu GPU (GPU 0) */
struct gpu_stat {
    /* Obecné info */
    char   name[128];
    int    index;          /* typicky 0 */
    bool   available;      /* false, pokud nvidia-smi / GPU není dostupná */

    /* Okamžité hodnoty */
    double utilization_percent;  /* 0–100 % */
    double temperature_celsius;  /* °C */
    double memory_used_mb;       /* MB */
    double memory_total_mb;      /* MB */
    double memory_used_percent;  /* 0–100 % */

    double core_clock_mhz;       /* core clock (MHz) */
    double mem_clock_mhz;        /* memory clock (MHz) */
    double power_watt;           /* aktuální spotřeba (W), pokud dostupná */
};

/* Inicializace struktury, zjištění zda je GPU / nvidia-smi dostupné */
void gpu_init(struct gpu_stat *gpu);

/* Aktualizace všech dynamických hodnot (usage, teplota, VRAM, frekvence, power) */
void gpu_update(struct gpu_stat *gpu);

/* Pomocné „getter“ funkce – konzistentní se system_variables API */
double gpu_get_utilization(const struct gpu_stat *gpu);
double gpu_get_temperature(const struct gpu_stat *gpu);
double gpu_get_memory_used_percent(const struct gpu_stat *gpu);
double gpu_get_core_clock(const struct gpu_stat *gpu); /* MHz */
double gpu_get_mem_clock(const struct gpu_stat *gpu);  /* MHz */
double gpu_get_power(const struct gpu_stat *gpu);      /* W */

#endif /* GPU_MONITOR_H */
