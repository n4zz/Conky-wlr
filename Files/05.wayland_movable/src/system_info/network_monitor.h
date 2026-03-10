#ifndef NETWORK_MONITOR_H
#define NETWORK_MONITOR_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*---------------------------------------------------------------------------------------------*/
//*     NETWORK
/*---------------------------------------------------------------------------------------------*/

struct network_stat {
    char interface[32];        // např. "wlan0", "eth0"

    // Celkové přenosy
    uint64_t rx_bytes;         // Celkem staženo (bytes)
    uint64_t tx_bytes;         // Celkem odesláno (bytes)

    // Rychlost (vyžaduje pravidelné update)
    uint64_t prev_rx_bytes;
    uint64_t prev_tx_bytes;
    double rx_speed_kbps;      // Download rychlost KB/s
    double tx_speed_kbps;      // Upload rychlost KB/s

    // WiFi specifické
    int signal_strength;       // Síla signálu v dBm (-100 až 0)
    int signal_percent;        // Síla signálu v % (0-100)
    bool is_wifi;              // true pokud je WiFi
    bool is_connected;         // true pokud je připojeno

    char address[64];          // IPv4 nebo IPv6 string

    bool valid;                // true pokud data jsou platná
};

void network_init(struct network_stat *net, const char *interface);
void network_init_auto(struct network_stat *net);
void network_update(struct network_stat *net);
void ip_update(struct network_stat *ip);

#endif
