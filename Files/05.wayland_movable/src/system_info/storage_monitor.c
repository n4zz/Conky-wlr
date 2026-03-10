#include "storage_monitor.h"
#include <stdio.h>
#include <sys/statvfs.h>
#include <string.h>


/*---------------------------------------------------------------------------------------------*/
//     STORAGE
/*---------------------------------------------------------------------------------------------*/

/* Zjistí název blokového zařízení (sda, nvme0n1, mmcblk0)
 * pro daný mount point (např. "/", "/home")
 */
static void get_device_name(const char *mount_point,
                            char *device_name,
                            size_t size)
{
    FILE *f = fopen("/proc/mounts", "r");
    if (!f) {
        device_name[0] = '\0';
        return;
    }

    char line[512];

    while (fgets(line, sizeof(line), f)) {
        char dev[256], mount[256];

        if (sscanf(line, "%255s %255s", dev, mount) != 2)
            continue;

        if (strcmp(mount, mount_point) != 0)
            continue;

        /* očekáváme /dev/sda1, /dev/nvme0n1p1, atd. */
        char *slash = strrchr(dev, '/');
        if (!slash)
            break;

        char tmp[64];
        strncpy(tmp, slash + 1, sizeof(tmp) - 1);
        tmp[sizeof(tmp) - 1] = '\0';

        /* nvme0n1p1 → nvme0n1 */
        char *p = strrchr(tmp, 'p');
        if (p && p[1] >= '0' && p[1] <= '9') {
            *p = '\0';
        } else {
            /* sda1 → sda, mmcblk0p1 → mmcblk0 */
            int len = strlen(tmp);
            while (len > 0 && tmp[len - 1] >= '0' && tmp[len - 1] <= '9') {
                tmp[--len] = '\0';
            }
        }

        strncpy(device_name, tmp, size - 1);
        device_name[size - 1] = '\0';

        fclose(f);
        return;
    }

    fclose(f);
    device_name[0] = '\0';
}

/* Přečte I/O statistiky pro disk */
void disk_update_io(struct disk_stat *disk)
{
    if (!disk || disk->device_name[0] == '\0')
        return;

    char path[256];
    snprintf(path, sizeof(path), "/sys/block/%s/stat", disk->device_name);

    FILE *f = fopen(path, "r");
    if (!f)
        return;

    unsigned long read_ios, read_merges, read_sectors, read_ticks;
    unsigned long write_ios, write_merges, write_sectors, write_ticks;

    if (fscanf(f, "%lu %lu %lu %lu %lu %lu %lu %lu",
               &read_ios, &read_merges, &read_sectors, &read_ticks,
               &write_ios, &write_merges, &write_sectors, &write_ticks) != 8) {
        fclose(f);
        return;
    }

    fclose(f);

    /* sektory jsou 512 B */
    uint64_t read_bytes  = read_sectors  * 512ULL;
    uint64_t write_bytes = write_sectors * 512ULL;

    uint64_t prev_read  = disk->read_bytes;
    uint64_t prev_write = disk->write_bytes;

    disk->read_bytes  = read_bytes;
    disk->write_bytes = write_bytes;

    if (prev_read > 0) {
        disk->read_speed_kbps  = (read_bytes  - prev_read)  / 1024.0;
        disk->write_speed_kbps = (write_bytes - prev_write) / 1024.0;
    } else {
        disk->read_speed_kbps  = 0.0;
        disk->write_speed_kbps = 0.0;
    }
}

void disk_init(struct disk_stat *disk, const char *mount_point)
{
    memset(disk, 0, sizeof(*disk));
    strncpy(disk->mount_point, mount_point, sizeof(disk->mount_point) - 1);

    // Zjistit název zařízení
    get_device_name(mount_point, disk->device_name, sizeof(disk->device_name));

    if (disk->device_name[0] != '\0') {
        printf("Disk: %s -> device: %s\n", mount_point, disk->device_name);
    }

    disk_update(disk);
    disk_update_io(disk); // První read pro baseline
}

void disk_update(struct disk_stat *disk)
{
    struct statvfs stat;

    if (statvfs(disk->mount_point, &stat) != 0) {
        disk->valid = false;
        return;
    }

    // Vypočítat velikosti v MB
    uint64_t block_size = stat.f_frsize;
    disk->total_mb = (stat.f_blocks * block_size) / (1024 * 1024);
    disk->free_mb = (stat.f_bfree * block_size) / (1024 * 1024);
    disk->used_mb = disk->total_mb - disk->free_mb;

    if (disk->total_mb > 0) {
        disk->percent = 100.0 * ((double)disk->used_mb / (double)disk->total_mb);
    } else {
        disk->percent = 0.0;
    }

    disk->valid = true;
    disk_update_io(disk);  // Update I/O stats
}
