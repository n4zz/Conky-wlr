
/* ==========================================
 * system_info_static.c - Implementation
 * ========================================== */

#include "system_info_static.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <pwd.h>

/*
 * Pomocná funkce - načte první řádek ze souboru
 */
static int read_first_line(const char *filepath, char *buffer, size_t size)
{
    FILE *fp = fopen(filepath, "r");
    if (!fp)
        return -1;
    
    if (fgets(buffer, size, fp) == NULL) {
        fclose(fp);
        return -1;
    }
    
    /* Odstranit newline na konci */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    
    fclose(fp);
    return 0;
}

/*
 * Pomocná funkce - spustí příkaz a načte jeho výstup
 */
static int read_command_output(const char *cmd, char *buffer, size_t size)
{
    FILE *fp = popen(cmd, "r");
    if (!fp)
        return -1;
    
    if (fgets(buffer, size, fp) == NULL) {
        pclose(fp);
        return -1;
    }
    
    /* Odstranit newline */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    
    pclose(fp);
    return 0;
}

/*
 * Získá informace o distribuci z lsb_release , /etc/os-release
 */
void get_distro_string(char *buffer, size_t size)
{
    char distro[256] = {0};
    char release[64] = {0};
    char codename[64] = {0};

    // 1) Pokus o lsb_release
    if (read_command_output("lsb_release -si 2>/dev/null", distro, sizeof(distro)) == 0 &&
        read_command_output("lsb_release -sr 2>/dev/null", release, sizeof(release)) == 0 &&
        read_command_output("lsb_release -sc 2>/dev/null", codename, sizeof(codename)) == 0)
    {
        snprintf(buffer, size, "%s %s (%s)", distro, release, codename);
        return;
    }

    // 2) Fallback: /etc/os-release
    FILE *fp = fopen("/etc/os-release", "r");
    if (!fp) {
        snprintf(buffer, size, "Unknown Linux");
        return;
    }

    char line[256];
    char name[256] = {0};
    char version[256] = {0};

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "NAME=", 5) == 0) {
            char *v = line + 5;
            if (*v == '"') v++;
            v[strcspn(v, "\"\n")] = 0;
            snprintf(name, sizeof(name), "%s", v);
        }
        if (strncmp(line, "VERSION_ID=", 11) == 0) {
            char *v = line + 11;
            if (*v == '"') v++;
            v[strcspn(v, "\"\n")] = 0;
            snprintf(version, sizeof(version), "%s", v);
        }
    }
    fclose(fp);

    if (name[0] == 0) snprintf(name, sizeof(name), "Linux");

    if (version[0] != 0)
        snprintf(buffer, size, "%s %s", name, version);
    else
        snprintf(buffer, size, "%s", name);
}

/*
 * Získá verzi kernelu pomocí uname()
 */
void get_kernel_version(char *buffer, size_t size)
{
    struct utsname uts;
    
    if (uname(&uts) == 0) {
        snprintf(buffer, size, "%s", uts.release);
    } else {
        snprintf(buffer, size, "Unknown");
    }
}

/*
 * Získá hostname
 */
void get_hostname(char *buffer, size_t size)
{
    if (gethostname(buffer, size) != 0) {
        snprintf(buffer, size, "localhost");
    }
}

/*
 * Získá uživatelské jméno
 */
void get_username(char *buffer, size_t size)
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    
    if (pw) {
        snprintf(buffer, size, "%s", pw->pw_name);
    } else {
        snprintf(buffer, size, "user");
    }
}

/*
 * Pokusí se detekovat desktop environment
 */
void get_desktop_env(char *buffer, size_t size)
{
    /* Zkusit environment proměnné */
    const char *xdg_current = getenv("XDG_CURRENT_DESKTOP");
    const char *desktop_session = getenv("DESKTOP_SESSION");
    const char *kde_full = getenv("KDE_FULL_SESSION");
    const char *wayland = getenv("WAYLAND_DISPLAY");
    
    if (kde_full && strcmp(kde_full, "true") == 0) {
        /* Zkusit získat verzi Plasma */
        char version[32] = "";
        if (read_command_output("plasmashell --version 2>/dev/null | awk '{print $2}'", 
                               version, sizeof(version)) == 0) {
            snprintf(buffer, size, "KDE Plasma %s", version);
        } else {
            snprintf(buffer, size, "KDE Plasma");
        }
    } else if (xdg_current) {
        snprintf(buffer, size, "%s", xdg_current);
    } else if (desktop_session) {
        snprintf(buffer, size, "%s", desktop_session);
    } else if (wayland) {
        snprintf(buffer, size, "Wayland");
    } else {
        snprintf(buffer, size, "Unknown");
    }
}

/*
 * Hlavní inicializační funkce
 */
void system_info_static_init(struct system_info_static *info)
{
    get_distro_string(info->distro_name, sizeof(info->distro_name));

    get_kernel_version(info->kernel_version, sizeof(info->kernel_version));
    
    get_hostname(info->hostname, sizeof(info->hostname));
    
    get_username(info->username, sizeof(info->username));
    
    get_desktop_env(info->desktop_env, sizeof(info->desktop_env));
}


void system_info_static_print(const struct system_info_static *info)
{
    if (!info)
        return;

    printf("System Info:\n");
    printf("  Distro: %s %s\n", info->distro_name, info->distro_version);
    printf("  Kernel: %s\n", info->kernel_version);
    printf("  Hostname: %s\n", info->hostname);
    printf("  User: %s\n", info->username);
    printf("  Desktop: %s\n", info->desktop_env);
}

