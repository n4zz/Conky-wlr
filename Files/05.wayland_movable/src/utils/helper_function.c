#define _GNU_SOURCE
#include "helper_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*---------------------------------------------------------------------------------------------*/
//     HELPER FUNction
/*---------------------------------------------------------------------------------------------*/

void format_bytes(uint64_t bytes, char *buffer, size_t buf_size)
{
    const char *units[] = {"B", "KB", "MB", "GB", "TB"};
    int unit_index = 0;
    double size = (double)bytes;

    while (size >= 1024.0 && unit_index < 4) {
        size /= 1024.0;
        unit_index++;
    }

    snprintf(buffer, buf_size, "%.2f %s", size, units[unit_index]);
}

uint64_t get_system_uptime(void)
{
    FILE *f = fopen("/proc/uptime", "r");
    if (!f) return 0;

    double uptime_seconds;
    if (fscanf(f, "%lf", &uptime_seconds) == 1) {
        fclose(f);
        return (uint64_t)uptime_seconds;
    }

    fclose(f);
    return 0;
}

const char* get_iface_type(const char* iface)
{
    if (strncmp(iface, "wl", 2) == 0)
        return "WiFi";
    if (strncmp(iface, "en", 2) == 0)
        return "Ethernet";
    if (strncmp(iface, "ww", 2) == 0)
        return "Mobile";
    if (strcmp(iface, "lo") == 0)
        return "Loopback";

    return "Unknown";
}
