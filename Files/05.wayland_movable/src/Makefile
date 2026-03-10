CC = gcc
CFLAGS = -Wall -Wextra -O2 -MMD -MP `pkg-config --cflags wayland-client cairo`
LDFLAGS = `pkg-config --libs wayland-client cairo`

OBJDIR = build/obj
DEPDIR = build/dep

SRC := wayland_movable.c xdg_move.c xdg-shell.c \
    $(wildcard orchestrator/*.c) \
    $(wildcard cairo_graphics/*.c) \
    $(wildcard config/*.c)\
    $(wildcard cairo_text/*.c) \
    $(wildcard system_info/*.c) \
    $(wildcard widgets/*.c)\
    $(wildcard utils/*.c)

OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
DEP := $(patsubst %.c,$(DEPDIR)/%.d,$(SRC))

all: wayland_movable

-include $(DEP)

wayland_movable: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@) $(DEPDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@mv $(basename $@).d $(DEPDIR)

clean:
	rm -rf build wayland_movable
