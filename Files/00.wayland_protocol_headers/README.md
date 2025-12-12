## Wayland Protocol Headers

This folder contains protocol files generated with **wayland-scanner**.  
These are required for features such as creating XDG toplevel windows.

---

### ➤ Generate protocol headers using `wayland-scanner`

#### xdg-shell.h — interface declarations

```sh
wayland-scanner client-header \
    /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml \
    xdg-shell.h
```

#### xdg-shell.c — protocol implementation

```sh
wayland-scanner private-code \
    /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml \
    xdg-shell.c
```

---

## ➤ Using the generated headers in your build

Example for a client that uses XDG surfaces:

```sh
gcc wayland_shm.c xdg-shell.c -o wayland_shm \
    $(pkg-config --cflags --libs wayland-client)
```

---

### Notes

- `xdg-shell.h` and `xdg-shell.c` must be generated once and committed to the repo.  
- They match the Wayland XML protocol located in `/usr/share/wayland-protocols/`.  
- Without these files, programs using `xdg_wm_base` will not link.

      
