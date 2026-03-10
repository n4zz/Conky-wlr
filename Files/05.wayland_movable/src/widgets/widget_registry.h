#ifndef WIDGET_REGISTRY_H
#define WIDGET_REGISTRY_H

#include "widget.h"
#include "../ui/ui_rect.h"

extern struct widget widgets[];
extern const int widget_count;
void widget_registry_apply_config(void);

#endif
