#include "cpu_monitor.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <dirent.h>


/*---------------------------------------------------------------------------------------------*/
//     CPU
/*---------------------------------------------------------------------------------------------*/
void cpu_init(struct cpu_stat *cpu)
{
    memset(cpu, 0, sizeof(*cpu));

    // Získat počet jader
    cpu->core_count = sysconf(_SC_NPROCESSORS_ONLN);

    // První update pro nastavení baseline
    cpu_update(cpu);
}

void cpu_update(struct cpu_stat *cpu)
{
    FILE *f = fopen("/proc/stat", "r");
    if (!f) {
        cpu->usage = 0.0;
        return;
    }

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

void cpu_get_frequency(struct cpu_stat *cpu)
{
    FILE *f = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");
    if (!f) {
        cpu->freq_mhz = 0.0;
        return;
    }

    unsigned long freq_khz;
    if (fscanf(f, "%lu", &freq_khz) == 1) {
        cpu->freq_mhz = freq_khz / 1000.0;
    } else {
        cpu->freq_mhz = 0.0;
    }
    fclose(f);
}

void cpu_get_temperature(struct cpu_stat *cpu)
{
    cpu->temp_celsius = 0.0;

    // Zkusit hwmon (nejběžnější pro moderní systémy)
    DIR *dir = opendir("/sys/class/hwmon");
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] == '.') continue;

            char path[512];
            snprintf(path, sizeof(path), "/sys/class/hwmon/%s/name", entry->d_name);

            FILE *name_f = fopen(path, "r");
            if (name_f) {
                char name[64];
                if (fgets(name, sizeof(name), name_f)) {
                    // Hledat coretemp, k10temp, zenpower, atd.
                    if (strstr(name, "coretemp") || strstr(name, "k10temp") ||
                        strstr(name, "zenpower") || strstr(name, "cpu_thermal")) {
                        fclose(name_f);

                        // Zkusit temp1_input (package temp)
                        snprintf(path, sizeof(path), "/sys/class/hwmon/%s/temp1_input", entry->d_name);
                        FILE *temp_f = fopen(path, "r");
                        if (temp_f) {
                            long temp_millidegree;
                            if (fscanf(temp_f, "%ld", &temp_millidegree) == 1) {
                                cpu->temp_celsius = temp_millidegree / 1000.0;
                                fclose(temp_f);
                                closedir(dir);
                                return;
                            }
                            fclose(temp_f);
                        }
                    } else {
                        fclose(name_f);
                    }
                } else {
                    fclose(name_f);
                }
            }
        }
        closedir(dir);
    }

    // Fallback: zkusit thermal_zone
    if (cpu->temp_celsius == 0.0) {
        FILE *f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
        if (f) {
            long temp_millidegree;
            if (fscanf(f, "%ld", &temp_millidegree) == 1) {
                cpu->temp_celsius = temp_millidegree / 1000.0;
            }
            fclose(f);
        }
    }
}
