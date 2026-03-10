#include "network_monitor.h"
//#include "../config/network_config.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*---------------------------------------------------------------------------------------------*/
//     NETWORK
/*---------------------------------------------------------------------------------------------*/

void network_init(struct network_stat *net, const char *interface)
{
    printf("NETWORK INIT USING INTERFACE: %s\n", interface);
    memset(net, 0, sizeof(*net));
    strncpy(net->interface, interface, sizeof(net->interface) - 1);

    // Zjistit jestli je to WiFi
    char path[512];
    snprintf(path, sizeof(path), "/sys/class/net/%s/wireless", interface);
    net->is_wifi = (access(path, F_OK) == 0);

    network_update(net);
}

void network_init_auto(struct network_stat *net)
{
    printf("NETWORK_INIT_AUTO START\n");
    // Zkusit najít aktivní síťové rozhraní
    const char *try_interfaces[] = {
        "wlan0", "wlp0s20f3", "wlp2s0", "wlp3s0", "wlp60s0",
        "eth0", "enp0s31f6", "eno1", "enp2s0",
        NULL
    };

    for (int i = 0; try_interfaces[i] != NULL; i++) {
        printf("AUTO-DETECT TRY: %s\n", try_interfaces[i]);
        char path[512];
        snprintf(path, sizeof(path), "/sys/class/net/%s/operstate", try_interfaces[i]);

        FILE *f = fopen(path, "r");
        if (f) {
            char state[32];
            if (fgets(state, sizeof(state), f)) {
                if (strncmp(state, "up", 2) == 0) {
                    fclose(f);
                    network_init(net, try_interfaces[i]);
                    return;
                }
            }
            fclose(f);
        }
    }

    // Fallback na wlan0
    network_init(net, "wlan0");
}

void network_update(struct network_stat *net)
{
    char path[512];

    // Zkontrolovat jestli je rozhraní aktivní
    snprintf(path, sizeof(path), "/sys/class/net/%s/operstate", net->interface);
    FILE *f = fopen(path, "r");
    if (f) {
        char state[32];
        if (fgets(state, sizeof(state), f)) {
            net->is_connected = (strncmp(state, "up", 2) == 0);
        }
        fclose(f);
    } else {
        net->valid = false;
        return;
    }

    // Přečíst RX bytes
    snprintf(path, sizeof(path), "/sys/class/net/%s/statistics/rx_bytes", net->interface);
    f = fopen(path, "r");
    if (f) {
        uint64_t rx;
        if (fscanf(f, "%lu", &rx) == 1) {
            // Vypočítat rychlost (pokud máme předchozí data)
            if (net->prev_rx_bytes > 0) {
                uint64_t diff = rx - net->prev_rx_bytes;
                net->rx_speed_kbps = diff / 1024.0;
            }
            net->prev_rx_bytes = net->rx_bytes;
            net->rx_bytes = rx;
        }
        fclose(f);
    }

    // Přečíst TX bytes
    snprintf(path, sizeof(path), "/sys/class/net/%s/statistics/tx_bytes", net->interface);
    f = fopen(path, "r");
    if (f) {
        uint64_t tx;
        if (fscanf(f, "%lu", &tx) == 1) {
            // Vypočítat rychlost (pokud máme předchozí data)
            if (net->prev_tx_bytes > 0) {
                uint64_t diff = tx - net->prev_tx_bytes;
                net->tx_speed_kbps = diff / 1024.0;
            }
            net->prev_tx_bytes = net->tx_bytes;
            net->tx_bytes = tx;
        }
        fclose(f);
    }

    // Přečíst WiFi sílu signálu (pokud je WiFi)
    if (net->is_wifi && net->is_connected) {
        snprintf(path, sizeof(path), "/proc/net/wireless");
        f = fopen(path, "r");
        if (f) {
            char line[256];
            // Přeskočit první dva řádky (hlavičky)
            fgets(line, sizeof(line), f);
            fgets(line, sizeof(line), f);

            // Přečíst data rozhraní
            while (fgets(line, sizeof(line), f)) {
                char iface[32];
                int status, link, level, noise;
                if (sscanf(line, " %31[^:]: %d %d. %d. %d.",
                          iface, &status, &link, &level, &noise) >= 3) {
                    if (strcmp(iface, net->interface) == 0) {
                        // link = 0–70
                        // převedeme na dBm (odhad, -90 až -30)
                        int dbm = -90 + (link * 60 / 70);

                        // normalizace na procenta jako KDE
                        int percent = (dbm + 90) * 100 / 60;

                        if (percent < 0) percent = 0;
                        if (percent > 100) percent = 100;

                        net->signal_strength = dbm;
                        net->signal_percent = percent;
                        break;
                    }
                }
            }
            fclose(f);
        }
    }

    net->valid = true;
}

void ip_update(struct network_stat *ip)
{
    struct ifaddrs *ifaddr, *ifa;
    ip->valid = false;
    ip->address[0] = '\0';

    if (getifaddrs(&ifaddr) == -1)
        return;

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr)
            continue;

        /* přeskoč loopback */
        if (strcmp(ifa->ifa_name, "lo") == 0)
            continue;

        if (ifa->ifa_addr->sa_family == AF_INET) {
            struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
            inet_ntop(AF_INET, &sa->sin_addr,
                      ip->address, sizeof(ip->address));
            ip->valid = true;
            break;
        }
    }

    freeifaddrs(ifaddr);
}
