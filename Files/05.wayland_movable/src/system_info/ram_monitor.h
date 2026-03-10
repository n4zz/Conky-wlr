#ifndef RAM_MONITOR_H
#define RAM_MONITOR_H

/*---------------------------------------------------------------------------------------------*/
//*     RAM
/*---------------------------------------------------------------------------------------------*/

struct ram_stat {
    unsigned long total_kb;
    unsigned long free_kb;
    unsigned long available_kb;
    unsigned long used_kb;
    double percent;               // Využití RAM v % (0-100)
};

void ram_update(struct ram_stat *ram);

#endif
