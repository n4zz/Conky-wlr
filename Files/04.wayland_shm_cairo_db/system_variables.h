#ifndef SYSTEM_VARIABLES_H
#define SYSTEM_VARIABLES_H

/*     CPU     */
struct cpu_stat {
    unsigned long long prev_total;
    unsigned long long prev_idle;
    double usage;
};

/* inicializace (první čtení) */
void cpu_init(struct cpu_stat *cpu);

/* aktualizace – volat jednou za tick */
void cpu_update(struct cpu_stat *cpu);


/*     RAM     */
struct ram_stat {
    unsigned long total_kb;
    unsigned long free_kb;
    unsigned long available_kb;
    unsigned long used_kb;
};

void ram_update(struct ram_stat *ram);

#endif
