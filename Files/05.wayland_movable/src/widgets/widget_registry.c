#include "../config/config_types.h"

#include "widget.h"
#include "clock.h"
#include "cpu_widget.h"
#include "gpu_widget.h"
#include "ram_widget.h"
#include "storage_widget.h"
#include "network_widget.h"
#include "sys_info_widget.h"


extern struct app_config g_config;  // Globální config

struct widget widgets[] = {

     /* ----- S Y S T E M   I N F O ---------------------------------------------*/
    { draw_sys_info_widget, NULL, {0,0,0,0} },

    /* ----- C P U -------------------------------------------------------------*/
    { draw_cpu_widget, NULL, {0,0,0,0} },


    /* ----- G P U -------------------------------------------------------------*/
    { draw_gpu_widget, NULL, {0,0,0,0} },

    /* ----- R A M -------------------------------------------------------------*/
    {draw_ram_widget, NULL, {0,0,0,0} },


    /* ----- S T O R A G E -----------------------------------------------------*/
    { draw_storage_widget, NULL, {0,0,0,0} },


    /* ----- N E T W O R K -----------------------------------------------------*/
    { draw_network_widget, NULL, {0,0,0,0} },


    /* ----- C L O C K ----------------------------------------------------------*/
    { draw_neon_clock, draw_neon_clock_marks, {0,0,0,0} },

};

void widget_registry_apply_config(void)
{
    widgets[0].bounds.x = g_config.widgets.sysinfo.x;
    widgets[0].bounds.y = g_config.widgets.sysinfo.y;
    widgets[0].bounds.w = g_config.widgets.sysinfo.width;
    widgets[0].bounds.h = g_config.widgets.sysinfo.height;

    widgets[1].bounds.x = g_config.widgets.cpu.x;
    widgets[1].bounds.y = g_config.widgets.cpu.y;
    widgets[1].bounds.w = g_config.widgets.cpu.width;
    widgets[1].bounds.h = g_config.widgets.cpu.height;

    widgets[2].bounds.x = g_config.widgets.gpu.x;
    widgets[2].bounds.y = g_config.widgets.gpu.y;
    widgets[2].bounds.w = g_config.widgets.gpu.width;
    widgets[2].bounds.h = g_config.widgets.gpu.height;

    widgets[3].bounds.x = g_config.widgets.ram.x;
    widgets[3].bounds.y = g_config.widgets.ram.y;
    widgets[3].bounds.w = g_config.widgets.ram.width;
    widgets[3].bounds.h = g_config.widgets.ram.height;

    widgets[4].bounds.x = g_config.widgets.storage.x;
    widgets[4].bounds.y = g_config.widgets.storage.y;
    widgets[4].bounds.w = g_config.widgets.storage.width;
    widgets[4].bounds.h = g_config.widgets.storage.height;

    widgets[5].bounds.x = g_config.widgets.network.x;
    widgets[5].bounds.y = g_config.widgets.network.y;
    widgets[5].bounds.w = g_config.widgets.network.width;
    widgets[5].bounds.h = g_config.widgets.network.height;

    widgets[6].bounds.x = g_config.widgets.clock.x;
    widgets[6].bounds.y = g_config.widgets.clock.y;
    widgets[6].bounds.w = g_config.widgets.clock.width;
    widgets[6].bounds.h = g_config.widgets.clock.height;
}

const int widget_count = sizeof(widgets) / sizeof(widgets[0]);
