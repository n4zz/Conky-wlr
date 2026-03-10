#pragma once
#include <cairo/cairo.h>

#include "../ui/ui_context.h"

#include "../system_info/cpu_monitor.h"
#include "../system_info/gpu_monitor.h"
#include "../system_info/ram_monitor.h"
#include "../system_info/network_monitor.h"
#include "../system_info/storage_monitor.h"
#include "../system_info/system_info_static.h"
#include "../cairo_graphics/history_graph.h"


void draw_all_widgets(cairo_t *cr, struct ui_context *ctx);

void draw_widget_registry(cairo_t *cr, struct ui_context *ctx);
