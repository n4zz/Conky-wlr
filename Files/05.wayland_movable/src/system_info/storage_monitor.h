#ifndef STORAGE_MONITOR_H
#define STORAGE_MONITOR_H

#include <stdint.h>
#include <stdbool.h>

/*---------------------------------------------------------------------------------------------*/
//*     STORAGE
/*---------------------------------------------------------------------------------------------*/
struct disk_stat {
    char mount_point[256];     // např. "/"
    char device_name[32];      // NOVÉ: např. "sda", "nvme0n1"

    uint64_t total_mb;         // Celkem MB
    uint64_t used_mb;          // Použito MB
    uint64_t free_mb;          // Volno MB
    double percent;            // Využití v % (0-100)

    // I/O statistics - NOVÉ
    uint64_t read_bytes;       // Celkem přečteno
    uint64_t write_bytes;      // Celkem zapsáno
    uint64_t prev_read_bytes;  // Pro výpočet rychlosti
    uint64_t prev_write_bytes;
    double read_speed_kbps;    // Rychlost čtení KB/s
    double write_speed_kbps;   // Rychlost zápisu KB/s

    bool valid;                // true pokud data jsou platná
};

void disk_init(struct disk_stat *disk, const char *mount_point);
//static void get_device_name(const char *mount_point, char *device_name, size_t size);
void disk_update(struct disk_stat *disk);
void disk_update_io(struct disk_stat *disk);

#endif
