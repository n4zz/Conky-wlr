#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include <string.h>

/*---------------------------------------------------------------------------------------------*/
//*     CPU
/*---------------------------------------------------------------------------------------------*/
struct cpu_stat {
    unsigned long long prev_total;
    unsigned long long prev_idle;
    double usage;              // CPU usage v % (0-100)
    double freq_mhz;           // Aktuální frekvence v MHz
    double temp_celsius;       // Teplota v °C
    int core_count;            // Počet jader
};

/* inicializace (první čtení) */
void cpu_init(struct cpu_stat *cpu);

/* aktualizace – volat jednou za tick */
void cpu_update(struct cpu_stat *cpu);

void cpu_get_frequency(struct cpu_stat *cpu);
void cpu_get_temperature(struct cpu_stat *cpu);

#endif
