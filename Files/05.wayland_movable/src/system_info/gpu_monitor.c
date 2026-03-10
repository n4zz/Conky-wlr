/* gpu_monitor.c
 *
 * Implementace monitoringu NVIDIA GPU pomocí nvidia-smi.
 * Čte usage, teplotu, paměť, frekvenci, spotřebu.
 */

#define _GNU_SOURCE
#include "gpu_monitor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* Interní helper – spustí nvidia-smi a vrátí FILE* */
static FILE *gpu_popen(const char *fmt, ...)
{
    char cmd[512];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(cmd, sizeof(cmd), fmt, ap);
    va_end(ap);

    return popen(cmd, "r");
}

/* Jednoduché trimování whitespace na konci */
static void rtrim(char *s)
{
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\r' || s[len - 1] == '\t')) {
        s[--len] = '\0';
    }
}

/* Inicializace – zjistit název GPU a jestli nvidia-smi funguje */
void gpu_init(struct gpu_stat *gpu)
{
    if (!gpu)
        return;

    memset(gpu, 0, sizeof(*gpu));
    gpu->index = 0;
    gpu->available = false;
    strcpy(gpu->name, "NVIDIA GPU");

    /* Zkusíme, zda nvidia-smi existuje a vrací data */
    FILE *fp = gpu_popen("nvidia-smi --query-gpu=name --format=csv,noheader,nounits -i %d 2>/dev/null", gpu->index);
    if (!fp) {
        return;
    }

    char line[256];
    if (fgets(line, sizeof(line), fp) != NULL) {
        rtrim(line);
        if (line[0] != '\0') {
            strncpy(gpu->name, line, sizeof(gpu->name) - 1);
            gpu->name[sizeof(gpu->name) - 1] = '\0';
            gpu->available = true;
        }
    }

    pclose(fp);
}

/* Interní helper – načte jednu řádku CSV bez headeru a rozparsuje */
static void gpu_parse_line(struct gpu_stat *gpu, const char *line)
{
    /* očekávaný formát:
     * utilization, temperature, mem_used, mem_total, core_clock, mem_clock, power
     * vše bez jednotek (csv,noheader,nounits)
     *
     * např: "15, 45, 512, 4096, 1500, 7000, 80"
     */

    if (!gpu || !line)
        return;

    double util = 0.0, temp = 0.0;
    double mem_used = 0.0, mem_total = 0.0;
    double core_clk = 0.0, mem_clk = 0.0;
    double power = 0.0;

    int count = sscanf(line, " %lf , %lf , %lf , %lf , %lf , %lf , %lf",
                       &util, &temp, &mem_used, &mem_total,
                       &core_clk, &mem_clk, &power);

    if (count >= 4) {
        gpu->utilization_percent = util;
        gpu->temperature_celsius = temp;
        gpu->memory_used_mb      = mem_used;
        gpu->memory_total_mb     = mem_total;
        if (gpu->memory_total_mb > 0.0) {
            gpu->memory_used_percent = (gpu->memory_used_mb / gpu->memory_total_mb) * 100.0;
        } else {
            gpu->memory_used_percent = 0.0;
        }
    }
    if (count >= 6) {
        gpu->core_clock_mhz = core_clk;
        gpu->mem_clock_mhz  = mem_clk;
    }
    if (count >= 7) {
        gpu->power_watt = power;
    }
}

/* Aktualizace dat přes nvidia-smi */
void gpu_update(struct gpu_stat *gpu)
{
    if (!gpu || !gpu->available)
        return;

    FILE *fp = gpu_popen(
        "nvidia-smi "
        "--query-gpu=utilization.gpu,temperature.gpu,memory.used,memory.total,clocks.sm,clocks.mem,power.draw "
        "--format=csv,noheader,nounits -i %d 2>/dev/null",
        gpu->index
    );

    if (!fp)
        return;

    char line[512];
    if (fgets(line, sizeof(line), fp) != NULL) {
        rtrim(line);
        gpu_parse_line(gpu, line);
    }

    pclose(fp);
}

/* Jednoduché „gettery“ – pokud není dostupné GPU, vrací 0 nebo NaN (podle preferencí) */

double gpu_get_utilization(const struct gpu_stat *gpu)
{
    if (!gpu || !gpu->available)
        return 0.0;
    return gpu->utilization_percent;
}

double gpu_get_temperature(const struct gpu_stat *gpu)
{
    if (!gpu || !gpu->available)
        return 0.0;
    return gpu->temperature_celsius;
}

double gpu_get_memory_used_percent(const struct gpu_stat *gpu)
{
    if (!gpu || !gpu->available)
        return 0.0;
    return gpu->memory_used_percent;
}

double gpu_get_core_clock(const struct gpu_stat *gpu)
{
    if (!gpu || !gpu->available)
        return 0.0;
    return gpu->core_clock_mhz;
}

double gpu_get_mem_clock(const struct gpu_stat *gpu)
{
    if (!gpu || !gpu->available)
        return 0.0;
    return gpu->mem_clock_mhz;
}

double gpu_get_power(const struct gpu_stat *gpu)
{
    if (!gpu || !gpu->available)
        return 0.0;
    return gpu->power_watt;
}


