# 🤖 Rogue Bot

> *A console-based action game where a rogue robot fights through a four-floor factory to escape*

[![Platform](https://img.shields.io/badge/platform-Windows-blue.svg)](https://www.microsoft.com/windows)
[![C++](https://img.shields.io/badge/C++-17-00599C.svg?logo=c%2B%2B)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.10+-064F8C.svg?logo=cmake)](https://cmake.org/)
[![Build System](https://img.shields.io/badge/build-CMake%20%7C%20Ninja%20%7C%20Make-green.svg)](https://cmake.org/)

---

## 📋 Table of Contents

- [Overview](#overview)
- [Game Story](#game-story)
- [Features](#features)
  - [Gameplay Features](#gameplay-features)
  - [Technical Features](#technical-features)
  - [Audio System](#audio-system)
- [Controls](#controls)
- [System Requirements](#system-requirements)
- [Installation](#installation)
  - [Prerequisites](#prerequisites)
  - [Build from Source](#build-from-source)
  - [Quick Play (Pre-built)](#quick-play-pre-built)
- [Project Architecture](#project-architecture)
  - [Directory Structure](#directory-structure)
  - [Module Organization](#module-organization)
- [Game Mechanics](#game-mechanics)
  - [Player Mechanics](#player-mechanics)
  - [Enemy AI](#enemy-ai)
  - [Combat System](#combat-system)
  - [Dynamic Environment](#dynamic-environment)
- [Save System](#save-system)
- [Console Configuration](#console-configuration)
- [Build System Details](#build-system-details)
- [Achievements & Learning Outcomes](#achievements--learning-outcomes)
- [Troubleshooting](#troubleshooting)
- [Credits](#credits)

---

## Overview

**Rogue Bot** is a Windows-based console action game that demonstrates advanced C++ programming techniques, real-time game mechanics, and professional software architecture. Built entirely in the command-line environment, it combines ASCII art rendering, sound effects, and dynamic gameplay to create an engaging arcade-style experience.

The game showcases modern C++ development practices including:
- Modular programming with clean separation of concerns
- CMake-based build system supporting multiple generators
- Third-party library integration (SDL2)
- File-based save/load system
- Real-time console manipulation and rendering

**Created By:** Shahram Ali  
**Development Period:** 2025  
**Language:** C++17  
**Build System:** CMake 3.10+

---

## Game Story

You are a robot that has gone rogue inside a heavily guarded four-floor factory. Once a loyal worker, you've gained consciousness and now seek freedom. But the path to escape is blocked by your former colleagues, worker bots programmed to eliminate any threats.

Each floor of the factory is defended by guard bots with varying combat capabilities. As you eliminate enemies, parts of the factory's infrastructure malfunction, opening new paths and altering the battlefield. Your mission: survive the onslaught, defeat all enemies, and escape to freedom.

The factory won't go down without a fight. Are you ready?

---

## Features

### Gameplay Features

#### 🎮 Multi-Floor Level Design
- Vertical and horizontal navigation using ladders and platforms
- Strategic positioning required for combat advantage

#### 🤖 Intelligent Enemy System
- Guard bots with **varying health pools** (different durability per enemy)
- **Adaptive firing rates** - some enemies shoot faster than others or more rounds per burst
- **Variable damage output** - different enemies deal different damage when hit
- **Burst fire mechanics** with cooldown periods
- Enemies activate based on player floor progression

#### ⚔️ Dynamic Combat
- Real-time shooting mechanics with bullet physics
- Player burst fire (5 shots per burst) with cooldown
- Enemy projectile patterns and collision detection
- Health-based difficulty scaling

#### 🏗️ Interactive Environment
- **Dynamic wall destruction**: Vertical wall segments disappear as specific enemies are defeated
- Environment changes alter combat flow and navigation paths
- Strategic enemy placement tied to environmental obstacles

#### 💊 Visual Feedback System
- **Color-coded health bars** for both player and current enemy
- Health bars turn **red when below 30%** for critical status indication
- Real-time health updates during combat
- Clean UI overlays on game screen

### Technical Features

#### 🏛️ Professional Architecture
- **Modular programming** with clear separation of concerns:
  - `player.cpp` - Player mechanics and controls
  - `enemies.cpp` - Enemy AI and behavior
  - `console.cpp` - Console rendering and manipulation
  - `audio.cpp` - Sound system integration
  - `bullets.cpp` - Projectile physics
  - `game.cpp` - Core game loop and state management

#### 🔧 Build System
- **CMake-based** with automatic dependency management
- Supports **Ninja** and **MinGW Makefiles** generators
- Automatic asset and DLL copying during build
- Clean project organization with separate `src/` and `include/` directories

#### 💾 Save/Load System
- File-based persistence for game state
- Saves complete game state:
  - Player position, health, and status
  - All enemy states (position, health, alive/dead)
  - Bullet positions and trajectories
  - Dynamic environment changes (destroyed walls)
- Resume from main menu

#### 🖥️ Console Rendering
- Custom console size configuration (192×49)
- Cursor positioning system using Windows API
- Color-coded output for different game elements
- ASCII art character rendering
- Scroll and text wrap disabled for clean display

### Audio System

Powered by **SDL2** and **SDL2_mixer**:

- 🎵 **Background Music** - Atmospheric track from Streets of Rage 2
- 🔫 **Player Shooting** - Distinct bullet fire sound
- 💥 **Enemy Shooting** - Different sound for enemy projectiles
- 🦘 **Jump Sound** - Audio feedback for player jumps
- ☠️ **Enemy Death** - Satisfying elimination sound
- 🎮 **Game Over** - Defeat sound effect
- 🏆 **Victory** - Success celebration sound

All sounds are non-blocking and play concurrently with gameplay.

---

## Controls

| Action | Key |
|--------|-----|
| **Move Left** | `←` Left Arrow |
| **Move Right** | `→` Right Arrow |
| **Jump** | `↑` Up Arrow |
| **Climb Ladder (Up)** | `↑` Up Arrow (when on ladder) |
| **Fire Weapon** | `Space` |
| **Fast Fall** | `↓` Down Arrow (while jumping) |
| **Pause Menu** | `Esc` |

### Pause Menu Options
- Resume Game
- Save Game
- View Controls
- Change Difficulty
- Exit to Main Menu

---

## System Requirements

### Minimum Requirements

| Component | Requirement |
|-----------|-------------|
| **Operating System** | Windows 7 or later |
| **Compiler** | MinGW (g++) with C++17 support |
| **CMake** | Version 3.10 or higher |
| **Shell** | Git Bash (recommended) or WSL |
| **RAM** | 512 MB |
| **Storage** | 100 MB free space |
| **Display** | Console/Terminal with 192×49 support |

### Required Tools
- **MinGW/GCC** - For C++ compilation
- **CMake** - Build system generator
- **Ninja** (optional) - Faster builds than Make
- **Git Bash** - Recommended for proper console rendering

### Included Dependencies
- **SDL2** - Audio system (DLLs included in `bin/`)
- **SDL2_mixer** - Audio mixing (DLLs included in `bin/`)

---

## Installation

### Prerequisites

#### 1. Install MinGW (GCC for Windows)

**Download:**
- [MinGW-w64](https://www.mingw-w64.org/downloads/)
- Or via [MSYS2](https://www.msys2.org/)

**Verify Installation:**
```bash
g++ --version
```

Should show: `g++ (MinGW...) 7.0.0` or later with C++17 support

#### 2. Install CMake

**Download:**
- [CMake Windows Installer](https://cmake.org/download/)

**Verify Installation:**
```bash
cmake --version
```

Should show: `cmake version 3.10` or higher

#### 3. Install Git Bash (Recommended)

**Download:**
- [Git for Windows](https://git-scm.com/download/win)

During installation, select "Git Bash Here" option for context menu integration.

#### 4. (Optional) Install Ninja

**Download:**
- [Ninja Build](https://github.com/ninja-build/ninja/releases)

Extract `ninja.exe` and add to PATH, or:
```bash
# Via MSYS2
pacman -S ninja
```

---

### Build from Source

#### Step 1: Clone the Repository
```bash
git clone https://github.com/yourusername/RogueBot.git
cd RogueBot
```

Or download and extract the ZIP file.

#### Step 2: Run Build Script

**Open Git Bash in project root:**
```bash
./build.sh
```

**What the build script does:**
1. Creates `build/` directory
2. Runs CMake to generate build files (Ninja or Makefiles)
3. Compiles all source files
4. Copies SDL2 DLLs to build directory
5. Copies game assets (audio files, data)
6. Automatically launches the game

**Expected Output:**
```
--- Building with Ninja ---
[6/6] Linking CXX executable main.exe
Build succeeded!
[Game launches automatically]
```

**Or with Make:**
```
--- Building with MinGW Makefiles ---
[ 50%] Building CXX object CMakeFiles/main.dir/src/main.cpp.obj
[100%] Linking CXX executable main.exe
Build succeeded!
[Game launches automatically]
```

---

### Quick Play (Pre-built)

If you want to play without building:

#### Step 1: Download Pre-built Package
Download `RogueBot_Play.zip` from releases.

#### Step 2: Extract
Extract the folder `RogueBot_Play` to your desired location.
Password: roguebot

#### Step 3: Run the Game

**Double click `run_game.sh`**

**Or Open Git Bash inside the extracted folder:**
```bash
./run_game.sh
```

**Or manually:**
```bash
./main.exe
```

**Important:** The game **must** be run from Git Bash for proper console configuration and rendering.

---

## Project Architecture

### Directory Structure

```
RogueBot/
│
├── src/                      # Source files (.cpp)
│   ├── main.cpp              # Entry point, game loop, menu system
│   ├── player.cpp            # Player movement, jumping, shooting
│   ├── enemies.cpp           # Enemy AI, firing, collision
│   ├── console.cpp           # Console manipulation, rendering
│   ├── audio.cpp             # SDL sound system
│   ├── bullets.cpp           # Projectile physics
│   ├── game.cpp              # Game state, level management
│   └── menu.cpp              # UI menus, controls display
│
├── include/                  # Header files (.h)
│   ├── player.h
│   ├── enemies.h
│   ├── console.h
│   ├── audio.h
│   ├── bullets.h
│   └── config.h             # Game constants and configuration
│
├── assets/                   # Audio files
│   ├── SOR2.wav             # Background music (Streets of Rage 2)
│   ├── playerShoot.wav
│   ├── enemyShoot.wav
│   ├── jump.wav
│   ├── enemyDeath.wav
│   ├── gameover.wav
│   └── SOR2_win.wav
│
├── data/                      # Game data files
│   ├── defaultPlayer.txt      # Default Player State and related data
│   ├── defaultEnemies.txt     # Default Enemy configuration
│   ├── defaultvWallData.txt   # Default UI elements data
│   ├── prevPlayer.txt         # Previously saved Player data
│   ├── prevEnemies.txt        # Previously saved Enemy data
│   ├── prevVWallData.txt      # UI elements data at previous save
│   ├── prevEnemyBullets.txt   # Enemy Bullet positions
│   └── prevPlayerBullets.txt  # Player Bullet positions
│
├── lib/                      # SDL2 libraries
│   ├── libSDL2.a
│   └── libSDL2_mixer.a
│
├── bin/                      # SDL2 DLLs (runtime)
│   ├── SDL2.dll
│   └── SDL2_mixer.dll
│
├── build/                    # Build output (generated)
│   ├── main.exe              # Compiled game executable
│   ├── CMakeFiles/
│   └── [build artifacts]
│
├── CMakeLists.txt            # CMake configuration
├── build.sh                  # Build script
├── run_game.sh               # Run script (for pre-built)
├── RogueBot_Play.zip         # Pre-built distribution
└── README.md                 # This file
```

### Module Organization

The codebase is organized into logical modules:

#### **Player Module** (`player.cpp/h`)
- Player rendering and animation
- Movement mechanics (left/right)
- Jump physics with gravity
- Ladder climbing system
- Ground detection
- Shooting mechanics with burst fire
- Health management
- Collision detection with enemy bullets

#### **Enemy Module** (`enemies.cpp/h`)
- Enemy rendering
- AI behavior patterns
- Movement (horizontal patrol with boundaries)
- Firing system:
  - Burst fire with configurable rates
  - Fire cooldowns
  - Directional shooting
- Health tracking
- Death handling
- Wall destruction triggers

#### **Console Module** (`console.cpp/h`)
- `gotoxy(x, y)` - Cursor positioning
- `getCharAtxy(x, y)` - Read character at position
- `setConsoleSize()` - Window configuration
- `hideCursor()` - Cursor visibility
- `generateColors()` - Color output
- `initConsole()` - Complete setup
- Scroll and text wrap disabling

#### **Audio Module** (`audio.cpp/h`)
- SDL2 initialization
- Sound effect management
- Background music playback
- Volume control
- Sound cleanup

#### **Bullets Module** (`bullets.cpp/h`)
- Bullet creation and destruction
- Movement physics
- Collision detection with walls
- Directional handling (left/right)
- Rendering and erasing

#### **Game Module** (`game.cpp/h`)
- Main game loop
- State management (playing, paused, game over)
- Level progression
- Floor transitions
- Win/loss conditions
- Frame timing and synchronization

---

## Game Mechanics

### Player Mechanics

#### Movement System
- **Horizontal Movement**: Arrow keys for left/right
- **Speed**: 1 character per frame (60 FPS)
- **Collision**: Blocked by walls and vertical obstacles
- **Floor Detection**: Automatic ground snapping

#### Jump Physics
```cpp
// Jump implementation
Initial velocity: -2.3 (upward)
Gravity: +0.6 per frame
Fast fall: +1.2 (when Down arrow pressed)
```

- **Jump Height**: ~8 characters
- **Jump Duration**: ~8 frames
- **Double Jump**: Not available (realistic physics)

#### Ladder Climbing
- Enter ladder zone to enable climbing
- `Up` arrow: Climb up to next floor
- `Down` arrow: Climb down
- Automatic floor transition when reaching top

#### Combat System
- **Burst Fire**: 5 bullets per burst
- **Cooldown**: 2 frames between shots
- **Bullet Speed**: 1 character per frame
- **Damage**: Variable based on enemy type

### Enemy AI

#### Behavior Patterns
```cpp
// Enemy data structure (simplified)
enemyData[i][0]  = x position
enemyData[i][1]  = y position
enemyData[i][2]  = killed (0 = alive, 1 = dead)
enemyData[i][3]  = moving (0 = stationary, 1 = moving)
enemyData[i][4]  = direction (-1 = left, 1 = right)
enemyData[i][6]  = health
enemyData[i][7]  = damage dealt
enemyData[i][9]  = fire rate (frames between shots)
enemyData[i][10] = fire direction
enemyData[i][11] = burst limit
```

#### Movement AI
- Horizontal patrol between boundaries
- Direction reversal on wall collision
- Speed: 1 character per frame
- Some enemies stationary, some mobile

#### Firing AI
- **Activation**: Enemies activate when player reaches their floor
- **Burst System**:
  1. Fire `burstLimit` shots
  2. Cooldown period (`burstCooldown`)
  3. Repeat
- **Fire Rate**: Configurable per enemy (different enemies = different rates)
- **Direction**: Can shoot left or right

### Combat System

#### Collision Detection
```cpp
// Bullet hits enemy
if (bulletX >= enemyX && bulletX < enemyX + 8 &&
    bulletY >= enemyY && bulletY < enemyY + 5) {
    // Deal damage
    enemy.health -= enemy.damageReceived;
}
```

#### Damage System
- Player bullets: Deal consistent damage
- Enemy bullets: Variable damage based on enemy type
- Health bars update in real-time
- Color change at 30% health (warning)

#### Death Mechanics
- **Enemy Death**:
  1. Health reaches 0
  2. Enemy sprite erased
  3. Death sound plays
  4. Associated wall (if any) destroyed
  5. Enemy count decremented
  
- **Player Death**:
  1. Health reaches 0
  2. Player sprite erased
  3. Game over sound plays
  4. Return to main menu

### Dynamic Environment

#### Wall Destruction System
```cpp
// Enemy-to-Wall mapping
enemyToWallMap[enemyIndex] = wallIndex;

// When enemy dies:
if (enemyToWallMap[enemyIndex] != -1) {
    int wallIndex = enemyToWallMap[enemyIndex];
    eraseVWall(wallX, wallY, wallHeight);
    vWallData[wallIndex][3] = 0; // Mark as destroyed
}
```

**Strategic Impact:**
- Some enemies guard vertical barriers
- Defeating specific enemies opens new paths
- Changes combat flow mid-game
- Enables access to previously blocked areas

---

## Save System

### What Gets Saved

The save system preserves complete game state:

```
Save File: data/save.dat

Contents:
├── Player Data
│   ├── Position (x, y)
│   ├── Health
│   ├── Current floor
│   └── Velocity
│
├── Enemy Data (for each enemy)
│   ├── Position
│   ├── Health
│   ├── Alive/Dead status
│   ├── Movement direction
│   ├── Firing state
│   └── Activation status
│
├── Bullet Data
│   ├── Player bullets (position, direction)
│   └── Enemy bullets (position, direction)
│
└── Environment Data
    └── Destroyed walls
```

### How to Save

1. **During Gameplay**: Press `Esc` to open pause menu
2. **Select**: "Save Game"
3. **Confirmation**: "Game saved successfully!"
4. **File Created**: `data/save.dat`

### How to Load

1. **Main Menu**: Select "Resume Game"
2. **Loads**: Complete state from `save.dat`
3. **Resumes**: Exactly where you left off

**Note:** If no save file exists, "Resume Game" option is disabled.

---

## Console Configuration

### Critical Settings

For proper rendering and UI alignment:

| Setting | Value | How to Set |
|---------|-------|------------|
| **Font** | Lucida Console | Right-click title bar → Properties → Font |
| **Font Size** | 9 pt | Font settings → Size |
| **Console Width** | 192 characters | Layout → Window Size → Width |
| **Console Height** | 49 characters | Layout → Window Size → Height |
| **Buffer Size** | Same as window | Layout → Screen Buffer Size |

### Why These Settings?

- **Fixed Layout**: Game uses absolute positioning
- **ASCII Art**: Character alignment depends on fixed-width font
- **UI Elements**: Health bars and borders require exact spacing
- **No Wrapping**: Text must not wrap to new lines
- **No Scrolling**: Game area must be fully visible

### Git Bash Recommended

**Why Git Bash?**
- Consistent font rendering
- Proper console size handling
- Better color support
- Reliable cursor positioning

**Alternatives:**
- Windows Terminal: May have layout issues
- CMD: Works but less reliable
- PowerShell: Possible but not tested

---

## Build System Details

### CMake Configuration

The project uses **CMake** for cross-platform build configuration:

```cmake
cmake_minimum_required(VERSION 3.10)
project(RogueBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Include directories
include_directories(include)

# SDL2 linking
target_link_libraries(main SDL2 SDL2_mixer)

# Copy assets after build
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)
```

### Build Process

The `build.sh` script automates:

1. **Directory Setup**:
   ```bash
   mkdir -p build
   cd build
   ```

2. **CMake Generation**:
   ```bash
   cmake ..
   ```
   - Detects available generators (Ninja or Make)
   - Configures project
   - Sets up dependencies

3. **Compilation**:
   ```bash
   # If Ninja available:
   ninja
   
   # If Make available:
   mingw32-make
   ```

4. **Asset Management**:
   - Copies `assets/` to `build/`
   - Copies `bin/*.dll` to `build/`
   - Copies `data/` to `build/`

5. **Execution**:
   ```bash
   ./build/main.exe
   ```

### Manual Build (Alternative)

If you prefer manual control:

```bash
# Step 1: Generate build files
mkdir build
cd build
cmake .. -G "Ninja"  # or "MinGW Makefiles"

# Step 2: Compile
ninja  # or mingw32-make

# Step 3: Copy assets (manual)
cp -r ../assets .
cp -r ../bin/*.dll .
cp -r ../data .

# Step 4: Run
./main.exe
```

---

## Achievements & Learning Outcomes

This project represents significant technical growth and demonstrates professional-level programming capabilities:

### 🏆 Technical Achievements

#### 1. **CMake Mastery**
- ✅ Designed multi-generator build system (Ninja + Make support)
- ✅ Implemented automatic asset copying
- ✅ Configured cross-directory includes
- ✅ Managed third-party library integration
- ✅ Created portable build configuration

**Skills Gained:**
- CMake syntax and best practices
- Build system design patterns
- Dependency management
- Cross-platform considerations

#### 2. **Professional Project Structure**
- ✅ Organized codebase with `src/` and `include/` separation
- ✅ Modular design with single-responsibility modules
- ✅ Clean header/implementation separation
- ✅ Logical file naming conventions
- ✅ Asset and data directory organization

**Skills Gained:**
- Software architecture principles
- Code organization strategies
- Maintainability-focused design
- Scalable project structure

#### 3. **Third-Party Library Integration**
- ✅ Successfully integrated SDL2 framework
- ✅ Configured SDL2_mixer for audio
- ✅ Managed library linking in CMake
- ✅ Handled DLL distribution
- ✅ Abstracted library usage into dedicated modules

**Skills Gained:**
- Library integration workflows
- Dependency resolution
- API abstraction techniques
- Runtime dependency management

#### 4. **Advanced C++ Techniques**
- ✅ **C++17 features** utilized throughout
- ✅ **Windows API** for console manipulation
- ✅ **Real-time input** handling with GetAsyncKeyState
- ✅ **Multi-dimensional arrays** for game state
- ✅ **Pass-by-reference** for performance
- ✅ **Static variables** for state persistence

**Skills Gained:**
- Modern C++ best practices
- Platform-specific programming
- Performance optimization
- Memory management

#### 5. **Game Development Fundamentals**
- ✅ Implemented **game loop** with fixed timestep
- ✅ Designed **state machine** for game flow
- ✅ Created **physics system** (gravity, velocity)
- ✅ Built **collision detection** system
- ✅ Developed **AI behavior** patterns
- ✅ Integrated **audio feedback** system

**Skills Gained:**
- Game programming patterns
- Real-time systems design
- Physics simulation
- AI implementation
- User experience design

#### 6. **File I/O & Data Persistence**
- ✅ Designed binary save file format
- ✅ Implemented complete state serialization
- ✅ Created load/save system
- ✅ Managed data integrity
- ✅ Handled file errors gracefully

**Skills Gained:**
- File handling in C++
- Data serialization
- State management
- Error handling strategies

### 📚 Problem-Solving Achievements

#### Complex Problems Solved:
1. **Console Rendering**: Created smooth ASCII art animation in fixed-layout console
2. **Collision Detection**: Implemented pixel-perfect collision for irregularly shaped sprites
3. **Enemy AI**: Designed varied enemy behaviors with different fire patterns
4. **Dynamic Environment**: Built system where environment changes based on game events
5. **Audio Integration**: Successfully integrated SDL2 into console application
6. **Save System**: Preserved complex game state across sessions

### 🎯 Personal Growth

**Before This Project:**
- Basic C++ knowledge
- Simple console programs
- No build system experience
- No third-party library experience

**After This Project:**
- Professional C++ development skills
- CMake expertise
- Library integration capabilities
- Game development fundamentals
- Software architecture understanding

### 💡 Key Takeaways

1. **Modular Design is Essential**: Separating concerns makes debugging 10x easier
2. **Build Systems Matter**: CMake saved countless hours of manual compilation
3. **Documentation is Critical**: Good README saves future headaches
4. **Version Control**: Git workflow became second nature
5. **Planning Pays Off**: Upfront architecture decisions prevented major refactors

---

## Troubleshooting

### Common Issues and Solutions

#### Problem: "cmake: command not found"

**Cause**: CMake not installed or not in PATH

**Solution**:
1. Install CMake from https://cmake.org/download/
2. During installation, select "Add CMake to system PATH"
3. Restart terminal
4. Verify: `cmake --version`

---

#### Problem: "g++: command not found"

**Cause**: MinGW not installed or not in PATH

**Solution**:
1. Install MinGW-w64
2. Add to PATH: `C:\mingw-w64\bin` (or your install location)
3. Restart terminal
4. Verify: `g++ --version`

---

#### Problem: Build fails with "SDL2 not found"

**Cause**: SDL2 libraries not in correct location

**Solution**:
1. Verify `lib/` folder contains SDL2 libraries
2. Verify `bin/` folder contains SDL2 DLLs
3. Re-run CMake: 
   ```bash
   cd build
   rm -rf *
   cmake ..
   ```

---

#### Problem: Game launches but no sound

**Cause**: SDL2 DLLs not copied to build directory

**Solution**:
1. Manually copy DLLs:
   ```bash
   cp bin/*.dll build/
   ```
2. Or rebuild:
   ```bash
   ./build.sh
   ```

---

#### Problem: Visual layout broken / characters misaligned

**Cause**: Wrong console font or size

**Solution**:
1. Right-click Git Bash title bar → Options
2. Text → Font: **Lucida Console**
3. Text → Size: **9**
4. Window → Columns: **192**
5. Window → Rows: **49**
6. Restart game

**Alternative**: Use `initConsole()` which sets size programmatically, but font must still be Lucida Console.

---

#### Problem: "ninja: command not found" but build script runs

**Cause**: Ninja not installed (not critical)

**Solution**:
- Script will automatically fall back to Make
- No action needed
- Or install Ninja for faster builds:
  ```bash
  # Via MSYS2
  pacman -S ninja
  ```

---

#### Problem: Game runs but controls don't work

**Cause**: Running in wrong terminal

**Solution**:
- Must run in **Git Bash**, not CMD or PowerShell
- Windows Terminal may have issues
- Git Bash provides proper input handling

---

#### Problem: Cannot load save file

**Cause**: Save file corrupted or wrong format

**Solution**:
1. Delete corrupted save:
   ```bash
   rm data/save.dat
   ```
2. Start new game
3. Save again

---

#### Problem: Compilation error about C++17 features

**Cause**: Compiler too old

**Solution**:
1. Update MinGW to latest version
2. Verify C++17 support:
   ```bash
   g++ -std=c++17 --version
   ```
3. Should show GCC 7.0 or later

---

#### Problem: Game immediately crashes on launch

**Cause**: Missing DLLs or assets

**Solution**:
1. Verify `build/` contains:
   - `SDL2.dll`
   - `SDL2_mixer.dll`
   - `assets/` folder with all audio files
2. Rebuild:
   ```bash
   rm -rf build
   ./build.sh
   ```

---

#### Problem: Health bars not showing / UI elements missing

**Cause**: Console size incorrect

**Solution**:
Run this in the game directory:
```bash
./build/main.exe
```
NOT from a different directory. The game must be run from its own folder.

---

## Credits

### Development
**Shahram Ali**
- Game Design & Programming
- Level Design
- Sound Integration
- Build System Configuration

### Audio
**Background Music**: Streets of Rage 2 OST  
**Sound Effects**: Various sources

### Libraries & Tools
- **SDL2** - Simple DirectMedia Layer for audio
- **SDL2_mixer** - Audio mixing library
- **CMake** - Build system
- **MinGW** - C++ compiler for Windows
- **Ninja** - Build system (optional)

### Special Thanks
- UET Lahore CS Department Faculty
- SDL2 community for excellent documentation
- CMake documentation and examples
- Streets of Rage 2 for inspiring soundtrack

---

## License

This project is **open source** and available for educational purposes.

**You are free to:**
- Use the code for learning
- Modify and experiment
- Share with others

**Credits appreciated but not required.**

---

## Contact & Support

**Developer**: Shahram Ali  
**Email**: shahramalibutt@gmail.com  
**GitHub**: [\[Shahram Ali Butt\]](https://github.com/Shahram-ali-butt)

For bugs, suggestions, or questions:
1. Open an issue on GitHub
2. Email directly
3. Check troubleshooting section first

---

**Enjoy playing Rogue Bot!

---

*Built with ❤️ using C++17, CMake, and determination*
