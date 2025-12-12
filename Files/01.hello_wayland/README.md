## Hello Wayland – Skeleton

A minimal, functional Wayland client without graphics.  
It connects to the compositor and creates a basic surface.

### ➤ Purpose (Milestone 3 foundation)

This file provides the groundwork for later steps:

- creates a Wayland surface  
- prepares the basis for rendering text, shapes, and later Lua-driven widgets  
- future additions may include:
  - text or shape rendering (Cairo / OpenGL)
  - Lua widget structure
  - testing under different compositors (Plasma, Sway, Hyprland)

---

## Instructions for build and test

### ➤ Install dependencies (Manjaro / Arch)

```sh
sudo pacman -S wayland wayland-protocols mesa
```

### ➤ Build

```sh
gcc hello_wayland.c -o hello_wayland $(pkg-config --cflags --libs wayland-client)
```

### ➤ Launch

```sh
./hello_wayland
```

---

If everything is OK, the program will print:

**Hello Wayland! Surface created successfully.**

