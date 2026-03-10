#include "draw_all.h"
#include <cairo/cairo.h>
#include "../config/config_types.h"

#include "widget_registry.h"
#include "../ui/ui_context.h"

#include "../cairo_graphics/cairo_shape.h"
#include "../cairo_graphics/main_window.h"

extern struct app_config g_config;

void draw_all_widgets(cairo_t *cr, struct ui_context *ctx)

/*---------------------------------------------------------------------------------------------*/
//             * C A I R O - D R A W I N G *
/*---------------------------------------------------------------------------------------------*/
            /* Clear background window (with transparency) */
{
            cairo_save(cr);
            cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
            cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.0);
            cairo_paint(cr);
            cairo_restore(cr);

/*---------------------------------------------------------------------------------------------*/
            /* Shapes */
            draw_frame_main(cr); // Dashboard okno s kulatými rohy a rámečkem
            draw_line_h(cr);     // Oddělovač

/*---------------------------------------------------------------------------------------------*/
            /* VYKRESLIT widgety */
            draw_widget_registry(cr, ctx);
/*---------------------------------------------------------------------------------------------*/
}


void draw_widget_registry(cairo_t *cr, struct ui_context *ctx)
{
    for (int i = 0; i < widget_count; i++) {
        struct widget *w = &widgets[i];

        bool enabled = true;

        switch (i) {
            case 0: enabled = g_config.widgets.sysinfo.enabled; break;
            case 1: enabled = g_config.widgets.cpu.enabled; break;
            case 2: enabled = g_config.widgets.gpu.enabled; break;
            case 3: enabled = g_config.widgets.ram.enabled; break;
            case 4: enabled = g_config.widgets.storage.enabled; break;
            case 5: enabled = g_config.widgets.network.enabled; break;
            case 6: enabled = g_config.widgets.clock.enabled; break;
        }

        if (!enabled)
            continue;


        if (w->draw1)
            w->draw1(cr, ctx, w->bounds);

        if (w->draw2)
            w->draw2(cr, ctx, w->bounds);
    }
}
