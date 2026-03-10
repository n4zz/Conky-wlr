/*
 * config_loader.h
 * -------------------------------------------
 * Načítání konfigurace z INI souborů
 */

#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include "config_types.h"

/*
 * Načte všechny config soubory a naplní g_config
 * 
 * Vrací:
 *   0 = úspěch
 *  -1 = chyba při načítání
 */
int config_load_all(void);

/*
 * Uloží aktuální config zpět do INI souborů
 * (pro budoucí použití)
 */
int config_save_all(void);

/*
 * Vytiskne aktuální config do stdout (pro debug)
 */
void config_print_debug(void);

#endif /* CONFIG_LOADER_H */
