## wayland_shm_cairo.c   

### ➤ What is this?      
      
Minimal example of a Wayland client using:
- wl_shm shared memory buffer
- xdg-shell (for window management)
- Cairo for 2D drawing     
      
### ➤ What does it do?
       
- Create Cairo surface from SHM buffer
- Draw text(s)
- Commit SHM buffer to Wayland surface     
     
--
     
## Instructions for build and test      

### ➤ Dependencies      
      
Ubuntu / Arch / Fedora — minimal set of required packages:       
       
- Ubuntu / Debian        
        
```sh        
sudo apt install build-essential pkg-config \
    libcairo2-dev libwayland-dev wayland-protocols
```      
         
- Arch / Manjaro        
         
```sh       
sudo pacman -S base-devel pkgconf \
    cairo wayland wayland-protocols
```         
             
- Fedora         
          
```sh          
sudo dnf install gcc pkgconf-pkg-config \
    cairo-devel wayland-devel wayland-protocols-devel
```             
        
### ➤ Generate xdg-shell headers           
                
xdg-shell.c and xdg-shell.h must be generated using wayland-scanner:           
             
```sh           
wayland-scanner client-header \
    /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml \
    xdg-shell.h
```              
              
```sh           
wayland-scanner private-code \
    /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml \
    xdg-shell.c
```                

### ➤  Build      
Ubuntu / Arch / Fedora — it works in all:
       
```sh      
gcc wayland_shm_cairo.c xdg-shell.c -o wayland_shm_cairo \
    $(pkg-config --cflags --libs wayland-client cairo)    
```         
         
### ➤ Launch
       
```sh      
./wayland_shm_cairo   
``` 
         
--      
      
### The program opens a window and draws texts using Cairo.  

--
       
### ➤ Known issues       
        
Common pitfalls when working with Wayland SHM + Cairo:       
        
- SHM buffer alignment         
Each row stride must be aligned to 4 bytes. Cairo usually handles this, but with manual SHM you must enforce alignment.        
          
- wl_surface_damage / damage_buffer        
Some compositors ignore the update if the full buffer isn't damaged or if damage regions are incorrect.       
       
- Cairo internal caching       
Cairo may not reflect SHM pixel changes unless a full redraw or cairo_surface_flush() is done.        
        
- Alpha channel         
SHM buffers with transparency behave differently across compositors (Sway OK, some KDE compositors ignore alpha).        
           
- No vsync control         
SHM clients have no direct vsync control → tearing may occur depending on compositor.        

