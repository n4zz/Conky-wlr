/* ==========================================
 * system_info_static.h - Static System Information
 * ========================================== */

#ifndef SYSTEM_INFO_STATIC_H
#define SYSTEM_INFO_STATIC_H

#include <stdlib.h>

/*
 * Statické systémové informace
 * Načtou se jednou při startu a nemění se
 */
struct system_info_static {
    char distro_name[128];      /* např. "Manjaro Linux" */
    char distro_version[64];    /* např. "23.1.0" */
    char kernel_version[128];   /* např. "6.6.8-2-MANJARO" */
    char hostname[128];         /* např. "mypc" */
    char username[64];          /* např. "user" */
    char desktop_env[64];       /* např. "KDE Plasma 6" */
};

/*
 * Načte statické systémové informace
 * Volá se jednou při startu programu
 */
void system_info_static_init(struct system_info_static *info);
void system_info_static_print(const struct system_info_static *info);


/*
 * Pomocné funkce pro získání jednotlivých informací
 */
void get_distro_info(char *name, size_t name_len,
                     char *version, size_t version_len);
void get_kernel_version(char *buffer, size_t size);
void get_hostname(char *buffer, size_t size);
void get_username(char *buffer, size_t size);
void get_desktop_env(char *buffer, size_t size);

#endif /* SYSTEM_INFO_STATIC_H */
