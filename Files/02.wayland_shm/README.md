## wayland_shm.c   

### ➤ What is this?      
      
Minimal example of drawing to a Wayland surface using wl_shm.      
Useful as a baseline for learning buffer creation, pool handling and direct pixel access.      
      
### ➤ What does it do?
       
- Connects to the Wayland server      
- Finds wl_shm      
- Creates an SHM pool using memfd      
- Creates a buffer      
- Fills it with a single-color background (e.g., blue)      
- Sends it to the screen      
     
--
     
## Instructions for build and test      

### ➤  Build      
Ubuntu / Arch / Fedora — it works in all:
       
```sh      
gcc wayland_shm.c -o wayland_shm $(pkg-config --cflags --libs wayland-client)      
```         
       
- For Cairo connection in the future:      
      
```sh      
gcc wayland_shm.c -o wayland_shm $(pkg-config --cflags --libs wayland-client cairo)       
```      
### ➤ Launch
       
```sh      
./wayland_shm   
``` 
         
--      
      
A 300×200 px rectangle with the color 0xFF2040A0 appears.      
