![GitHub issues](https://img.shields.io/github/issues/n4zz/Conky-wlr)
![GitHub forks](https://img.shields.io/github/forks/n4zz/Conky-wlr)
![GitHub stars](https://img.shields.io/github/stars/n4zz/Conky-wlr)
![License](https://img.shields.io/github/license/n4zz/Conky-wlr)      
```      
                        ____ ___  _   _ _  ____   __ __        ___     ____        
                       / ___/ _ \| \ | | |/ /\ \ / / \ \      / / |   |  _ \        
                      | |  | | | |  \| | ' /  \ V /___\ \ /\ / /| |   | |_) |        
                      | |__| |_| | |\  | . \   | |_____\ V  V / | |___|  _ <         
                       \____\___/|_| \_|_|\_\  |_|      \_/\_/  |_____|_| \_\       
```
## Love Conky and want it to run natively on Wayland?  
You're in the right place!

## 🎯 What is this project?           
         
This repository is an **experimental attempt to build a native Wayland backend for Conky**.                This repository is structured as a step-by-step exploration of Wayland rendering,
progressing from a minimal client to a modular widget framework.      
       
I’m **not a professional developer** — my experience comes mostly from small Bash, Python, HTML & CSS projects.           
But Conky deserves to run properly on Wayland without X11, XWayland, or hacks… so here we are.      
          
This project:        
- may take a long time,         
- may fail in some parts,         
- will definitely evolve,         
- is open to anyone who wants to experiment or contribute      
        
---       
        
## 🌟 Project Vision
- Build a **Wayland-native backend** for Conky         
- Support **text, graphs, and Lua-based widgets**           
- Provide **cross-compositor compatibility**          
- Encourage **community-driven experimentation and contributions**      
          
---      
        
## 🚀 Current Status
    Important. Current phase of the project - PAUSE. 
    Work is underway and a custom system widget for plasma (kwin).      
     
This repository currently serves as:      
- a **research sandbox**,        
- a learning space for Wayland + SHM + Cairo,        
- and a step-by-step progression toward a functional prototype.        
      
Milestones are updated manually as development progresses.       
          
| Milestone | Progress |      
|-----------|----------|        
| Project Foundation | 🔹 25% |       
| Wayland Architecture Research | 🔹 66% |        
| Prototype Rendering Layer | 🔹 66% |        
          
> See [Milestones](https://github.com/n4zz/Conky-wlr/milestones) for details.  
> Track issues progress [here](https://github.com/n4zz/Conky-wlr/issues).
      
---
       
## 📂 Repository Structure      
       
```
Files/
 ├── 00.wayland_protocol_headers/   → generated xdg-shell headers
 ├── 01.hello_wayland/              → minimal Wayland client test
 ├── 02.wayland_shm/                → SHM surface + raw drawing
 ├── 03.wayland_shm_cairo/          → SHM + Cairo rendering
 ├── 04.wayland_shm_cairo_db/       → SHM + Cairo + double buffer - widget prototype
 └── 05.wayland_movable             → SHM + Cairo + double buffer + xdg_move + config
Screenshots/                        → test output images
```
       
Each subdirectory contains its own `README.md` with instructions.      
       
---       
       
## 📦 Installation
*(Under development – instructions will be added once the prototype is ready.)*

---

## 📝 Contributing
  
It will be open to contributors once there is a functional basis.        
For now, it is being used for experimenting with Wayland.       
      
- See [CONTRIBUTING.md](./CONTRIBUTING.md) for detailed guidelines        
      
---

## 🎯 Milestones Overview
1. **Project Foundation** – setup, documentation, roadmap  
2. **Wayland Architecture Research** – backend study, rendering options, Lua feasibility  
3. **Prototype Rendering Layer** – minimal Wayland surface, text and shape rendering, placeholder for widgets
     
---         

## Development Path     
``` 
      hello_wayland (v01)
           │
           ▼
      Wayland SHM buffers (v02)
           │
           ▼
      SHM + Cairo rendering (v03)
           │
           ▼
      Double buffering (v03)
           │
           ▼
      Widget prototype (v04)
           │
           ▼
      Widget framework (v05)
```
     
## Development Progress      
      
  ✅ First step completed: `hello_wayland.c` skeleton created and successfully tested.
         
  This minimal Wayland client creates a surface and confirms the connection to the compositor.  
  [See file](https://github.com/n4zz/Conky-wlr/blob/main/Files/01.hello_wayland/hello_wayland.c)       
  
  ✅ Version 02 : SHM buffer allocation + drawing        
        
  Basic shared memory buffer rendering implemented.     
  [See file](https://github.com/n4zz/Conky-wlr/blob/main/Files/02.wayland_shm/wayland_shm.c)       
      
  ✅ Version 03 : Cairo-based text rendering      
         
  Text rendering using Cairo integrated with Wayland SHM buffers.      
  [See file](https://github.com/n4zz/Conky-wlr/blob/main/Files/03.wayland_shm_cairo/wayland_shm_cairo.c)      
           
  ✅ Version 04 : Modular rendering architecture - widget prototype       
        
      - real-time rendering (tick-based redraw)       
      - double buffering       
      - modular architecture       
      - dynamic system information (Time, CPU, RAM)       
      - transparency and alpha blending       
          
 [See files](https://github.com/n4zz/Conky-wlr/tree/main/Files/04.wayland_shm_cairo_db)
        
  ✅ Version 05 milestone: system widgets and window interaction
        Features introduced:
       
      - Cairo graphics and text rendering
      - system monitoring modules
      - modular widgets
      - configuration system
      - graphs and progress bars
      - drag-to-move window support (xdg_move)       
      
            
 [See files](https://github.com/n4zz/Conky-wlr/tree/main/Files/05.wayland_movable/src)      
       
## Architecture Overview        
 ```  
                Wayland Compositor
                        │
                        ▼
                Wayland Client
              (wayland_movable.c)
                        │
                        ▼
                SHM Buffer System
             (shared memory buffers)
                        │
                        ▼
                 Cairo Renderer
        ┌───────────────┼───────────────┐
        ▼               ▼               ▼     
   Shapes / UI      Text Rendering     Graphs      
 (cairo_graphics)   (cairo_text)     (progress/graphs)       
        │               │               │       
        └───────────────┴───────────────┘        
                        │      
                        ▼       
                    Widgets       
         (combine graphics + text + data)
                        │
                        ▼
                System Information
       CPU / RAM / GPU / Network / Storage
```
🔜 
---

## 🖼 Screenshots / Demos
      
### **Wayland_SHM**
[📄 View README](./Files/02.wayland_shm/README.md)  

<img src="https://github.com/n4zz/Conky-wlr/blob/main/Screenshots/wayland_shm_test.png" width="140">
       
---
              
### **Wayland_SHM_Cairo_text**      
[📄 View README](./Files/03.wayland_shm_cairo/README.md)  

<img src="https://github.com/n4zz/Conky-wlr/blob/main/Screenshots/wayland_shm_cairo_test.png" width="200">     
      
---

### **Wayland_SHM_Cairo_widget_prototype**      
[📄 View README](./Files/04.wayland_shm_cairo_db/README.md)  

<img src="https://github.com/n4zz/Conky-wlr/blob/main/Screenshots/wayland_shm_system_info.png" width="200">    <img src="https://github.com/n4zz/Conky-wlr/blob/main/Screenshots/transparency_test.png" width="200"> <img src="https://github.com/n4zz/Conky-wlr/blob/main/Screenshots/transparency_test_2.png" width="200"> <img src="https://github.com/n4zz/Conky-wlr/blob/main/Screenshots/bgrd_wall_transparency_test.png" width="200">

---

### **Wayland_movable**      
[📄 View README](./Files/05.wayland_movable/README.md)       

<img src="https://github.com/n4zz/Conky-wlr/blob/main/Screenshots/v05_demo.png" width="200">       <img src="Screenshots/wayland_movable.gif" width="600">
       
---
       
## 📚 References
- [Conky](https://github.com/brndnmtthws/conky)  
- [Wayland](https://wayland.freedesktop.org/)
- [Wayland book](https://wayland-book.com/)
- wlroots Documentation  
- Cairo Graphics  
- Lua 5.x for widget scripts
      
---      
       
## 📝 Note      
       
This project is intended as a **personal experiment and community contribution**. There is no guarantee that everything will work immediately, but every step forward is welcome.



