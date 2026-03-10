#ifndef HELPER_FUNCTION_H
#define HELPER_FUNCTION_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

/*---------------------------------------------------------------------------------------------*/
//*     HELPER FUNCTION
/*---------------------------------------------------------------------------------------------*/

/* Převede bytes na čitelný formát (B, KB, MB, GB, TB) */
void format_bytes(uint64_t bytes, char *buffer, size_t buf_size);

/* Vrátí uptime systému v sekundách */
uint64_t get_system_uptime(void);

/* Vrátí Wifi/Ethernet/Mobile místo plného názvu připojení */
const char* get_iface_type(const char* iface);


/* ---------------------------------------------------------
   PŘEVODY
   --------------------------------------------------------- */

static inline double mb_to_gb(double mb) {
    return mb / 1024.0;
}

static inline double kb_to_mb(double kb) {
    return kb / 1024.0;
}

static inline double mhz_to_ghz(double mhz) {
    return mhz / 1000.0;
}

/* ---------------------------------------------------------
   FORMÁTOVÁNÍ MB -> GB
   --------------------------------------------------------- */

static inline void format_mb_or_gb(double mb, char *buf, size_t size) {
    if (mb >= 1024.0)
        snprintf(buf, size, "%.1f GB", mb / 1024.0);
    else
        snprintf(buf, size, "%.0f MB", mb);
}

/* ---------------------------------------------------------
   FORMÁTOVÁNÍ MHz -> GHz
   --------------------------------------------------------- */

static inline void format_mhz_or_ghz(double mhz, char *buf, size_t size) {
    if (mhz >= 1000.0)
        snprintf(buf, size, "%.2f GHz", mhz / 1000.0);
    else
        snprintf(buf, size, "%.0f MHz", mhz);
}

/* ---------------------------------------------------------
   FORMÁTOVÁNÍ kb/s -> Mb/s
   --------------------------------------------------------- */

static inline void format_speed_kbps(double kbps, char *buf, size_t size) {
    if (kbps >= 1024.0 * 1024.0) {
        snprintf(buf, size, "%.2f GB/s", kbps / (1024.0 * 1024.0));
    } else if (kbps >= 1024.0) {
        snprintf(buf, size, "%.1f MB/s", kbps / 1024.0);
    } else {
        snprintf(buf, size, "%.0f KB/s", kbps);
    }
}


#endif

