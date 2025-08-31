# 2D Game Engine

A modular, portable 2D game engine built with **C++** and **SDL**, designed to simplify game development with core systems such as animation, physics, input handling, camera control, map management, collision detection, and more.

##  Features

- **Animation** – Manage sprite animations with ease.
- **Camera** – Smooth camera movement and positioning.
- **Collision** – Axis-aligned bounding box (AABB) collision detection.
- **Graphics** – Render sprites and shapes with SDL.
- **Inputs** – Keyboard and mouse input abstraction.
- **Map** – Load and manage tile-based maps (e.g., via TinyXML).
- **Characters & Objects** – Entity/component systems for game objects.
- **Physics** – Basic movement, gravity, and collision response.
- **Timer** – Frame timing and delta-time calculation.
- **Modular Structure** – Clean separation of concerns for easier maintenance and extension.
- **TinyXML Integration** – XML parsing for map or config loading.

##  Getting Started

### Prerequisites

- **C++ Compiler** — GCC, Clang, or MSVC supporting C++11+  
- **SDL2** — Install via package manager or from [SDL website]  
- **TinyXML** — Bundled under `Vendor/` for convenience

### Building

1. Clone the repo:

   ```bash
   git clone https://github.com/Aditya-Singh-3112/2D-Game-Engine.git
   cd 2D-Game-Engine
2. Ensure SDL2 is installed and accessible by your compiler/linker.
3. g++ -std=c++11 main.cpp \
    Core/*.cpp Animation/*.cpp Camera/*.cpp Collision/*.cpp \
    Graphics/*.cpp Inputs/*.cpp Map/*.cpp Object/*.cpp Physics/*.cpp \
    Timer/*.cpp Vendor/TinyXML/*.cpp \
    -I Vendor/TinyXML -I path/to/SDL2/include \
    -L path/to/SDL2/lib -lSDL2 -lSDL2_image -lSDL2_ttf -o game_engine
# Usage
./game_engine

# Project Structure
├── Animation/       # Animation management
├── Camera/          # Camera handling
├── Characters/      # Character-specific logic
├── Collision/       # Collision detection modules
├── Core/            # Engine core files
├── Graphics/        # Rendering subsystem
├── Inputs/          # Input abstraction (keyboard/mouse)
├── Map/             # Tile/map loading handlers
├── Object/          # General game object management
├── Physics/         # Movement, gravity, collision response
├── Timer/           # Frame timing utilities
├── Vendor/
│   └── TinyXML/     # XML parsing library
├── assets/          # Sprites, levels, configs, etc.
├── bin/ Debug/      # Build outputs (binary/debug)
├── obj/ Debug/      # Object files
├── main.cpp         # Entry point for engine/demo
├── GameEngine.*     # Code::Blocks project files
└── README.md        # (This file)
