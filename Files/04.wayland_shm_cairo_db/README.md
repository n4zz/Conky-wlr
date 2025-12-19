# wayland_shm_cairo — Version 04

## Overview

Version **04** is a major step forward compared to version **03**.
While v03 was a **single-file experimental prototype**, v04 evolves into a **structured, extensible Wayland SHM + Cairo application** that demonstrates:

- real-time rendering (tick-based redraw)
- double buffering
- modular architecture
- dynamic system information (Time, CPU, RAM)
- transparency and alpha blending

This version can be considered a **functional foundation for Wayland widgets or lightweight system monitors**.

---

### Version 04 (current)
 
Version 04 introduces **architecture, timing, and state**.

Key improvements:

- **Modular codebase**
  - `wayland_shm_cairo.c` — core Wayland logic and main loop
  - `cairo_text.c/.h` — text rendering (Date, Time)
  - `cairo_shape.c/.h` — shapes and UI elements
  - `system_variables.c/.h` — CPU and RAM statistics

- **Double buffering** (two SHM buffers)
  - Prevents flickering
  - Ensures safe redraw while compositor owns the previous buffer

- **Tick-based main loop**
  - Uses `poll()` with 1s timeout
  - Clean separation between:
    - event handling
    - periodic updates
    - rendering

- **Dynamic system data**
  - CPU usage calculated from `/proc/stat`
  - RAM usage from `/proc/meminfo`
  - Values update every tick

- **Alpha transparency**
  - ARGB8888 SHM buffers
  - Semi-transparent background
  - Correct compositor blending verified visually

- **Improved rendering pipeline**
  - Full surface clear each frame (`CAIRO_OPERATOR_SOURCE`)
  - Deterministic redraw (no accumulation artifacts)

---

## Rendering Pipeline (v04)

High-level flow per frame:

1. **Wayland events** are dispatched (non-blocking)
2. `poll()` waits up to 1 second
3. On timeout (tick):
   - Update CPU / RAM statistics
   - Wait for a free SHM buffer (if needed)
   - Clear the buffer
   - Draw shapes
   - Draw text
   - Attach buffer to surface
   - Commit

This model is suitable for:
- clocks
- system monitors
- status widgets

---

## Main Loop Structure (important)

The main loop is intentionally structured into three conceptual parts:

- **Event handling**
- **Tick / update phase**
- **Render & commit phase**

This separation is critical for Wayland clients and is explicitly documented in code comments.

---

## Transparency Validation

Transparency was verified using:

- solid-color background quadrants
- wallpaper background

Results confirm:

- correct alpha blending
- compositor-side composition
- no SHM alpha corruption

---

## Build Instructions

### Dependencies

Ubuntu / Debian:

```
sudo apt install build-essential pkg-config \
    libcairo2-dev libwayland-dev wayland-protocols
```

Arch / Manjaro:

```
sudo pacman -S base-devel pkgconf \
    cairo wayland wayland-protocols
```

Fedora:

```
sudo dnf install gcc pkgconf-pkg-config \
    cairo-devel wayland-devel wayland-protocols-devel
```

---

### Generate xdg-shell headers

```
wayland-scanner client-header \
  /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml \
  xdg-shell.h
```

```
wayland-scanner private-code \
  /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml \
  xdg-shell.c
```

---

### Build

```
gcc wayland_shm_cairo_db.c cairo_text.c cairo_shape.c \
    system_variables.c xdg-shell.c \
    -o wayland_shm_cairo_db \
    $(pkg-config --cflags --libs wayland-client cairo)
```

---

### Run

```
./wayland_shm_cairo_db
```

---

## Known Limitations

- SHM clients have no vsync control
- Window positioning is compositor-controlled
- Not yet a layer-shell client (not a true desktop widget)

---

## Summary

Version 04 is no longer just a demo.

It is a **clean, documented, extensible Wayland SHM + Cairo foundation** suitable for:

- experiments
- learning Wayland internals
- future widget or backends


