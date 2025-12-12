![GitHub issues](https://img.shields.io/github/issues/n4zz/Conky-wlr)
![GitHub forks](https://img.shields.io/github/forks/n4zz/Conky-wlr)
![GitHub stars](https://img.shields.io/github/stars/n4zz/Conky-wlr)
![License](https://img.shields.io/github/license/n4zz/Conky-wlr)      
      
                        ____ ___  _   _ _  ____   __ __        ___     ____        
                       / ___/ _ \| \ | | |/ /\ \ / / \ \      / / |   |  _ \        
                      | |  | | | |  \| | ' /  \ V /___\ \ /\ / /| |   | |_) |        
                      | |__| |_| | |\  | . \   | |_____\ V  V / | |___|  _ <         
                       \____\___/|_| \_|_|\_\  |_|      \_/\_/  |_____|_| \_\       

## Love Conky and want it to run natively on Wayland?  
You're in the right place!

## 🎯 What is this project?           
         
This repository is an **experimental attempt to build a native Wayland backend for Conky**.          
         
I’m **not a professional developer** — my experience comes mostly from small Bash, Python, HTML & CSS projects.           
But Conky deserves to run properly on Wayland without X11, XWayland, or hacks… so here we are.      
          
This project:        
- may take a long time,         
- may fail in some parts,         
- will definitely evolve,         
- and **anyone is welcome to join or experiment**.        
        
---       
        
## 🌟 Project Vision
- Build a **Wayland-native backend** for Conky         
- Support **text, graphs, and Lua-based widgets**           
- Provide **cross-compositor compatibility**          
- Encourage **community-driven experimentation and contributions**      
          
---      
        
## 🚀 Current Status
      
This repository currently serves as:      
- a **research sandbox**,        
- a learning space for Wayland + SHM + Cairo,        
- and a step-by-step progression toward a functional prototype.        
          
| Milestone | Progress |      
|-----------|----------|        
| Project Foundation | 🔹 25% |       
| Wayland Architecture Research | 🔹 0% |        
| Prototype Rendering Layer | 🔹 0% |        
          
> See [Milestones](https://github.com/n4zz/Conky-wlr/milestones) for details.  
> Track issues progress [here](https://github.com/n4zz/Conky-wlr/issues).
      
---
       
## 📂 Repository Structure      
       
```
Files/
 ├── 00.wayland_protocol_headers/   → generated xdg-shell headers
 ├── 01.hello_wayland/              → minimal Wayland client test
 ├── 02.wayland_shm/                → SHM surface + raw drawing
 └── 03.wayland_shm_cairo/          → SHM + Cairo rendering
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
      
- U can see [CONTRIBUTING.md](./CONTRIBUTING.md) for detailed guidelines        
      
---

## 🎯 Milestones Overview
1. **Project Foundation** – setup, documentation, roadmap  
2. **Wayland Architecture Research** – backend study, rendering options, Lua feasibility  
3. **Prototype Rendering Layer** – minimal Wayland surface, text and shape rendering, placeholder for widgets
     
-          
       
- Milestone 3 – Prototype Rendering Layer  
  ✅ First step completed: `hello_wayland.c` skeleton created and successfully tested.  
  This minimal Wayland client creates a surface and confirms the connection to the compositor.  
  [See file](./hello_wayland.c)

  ✅ SHM buffer allocation + drawing  
      
  ✅ Cairo-based text rendering  
     
  🔜 Modular rendering architecture (planned for step 04)          
    
---

## 🖼 Screenshots / Demos
*(Add screenshots or ASCII examples here as project evolves)*

---

## 📚 References
- [Conky](https://github.com/brndnmtthws/conky)  
- [Wayland](https://wayland.freedesktop.org/) & wlroots documentation  
- wlroots Documentation  
- Cairo Graphics  
- Lua 5.x for widget scripts
      
---      
       
## Note      
       
This project is intended as a **personal experiment and community contribution**. There is no guarantee that everything will work immediately, but every step forward is welcome.



