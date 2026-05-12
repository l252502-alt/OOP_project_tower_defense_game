# Tower Defense Game

# Object Oriented Programming Semester Project

# 

# A Tower Defense game built in C++ using Object Oriented Programming concepts.

# Enemies spawn in waves and walk along a fixed path. You place defensive towers

# beside the path to stop them. Earn gold by defeating enemies and spend it on

# more towers. Survive all 5 waves to win.

# 

# How to Compile and Run

# 

# \-Requirements

# \- Windows 10 or 11

# \- Visual Studio 2019 or 2022

# \- SFML 2.6.1

# 

# \-Download and Extract SFML

# 

# 1\. Go to: \*\*https://sfml-dev.org/download.php\*\*

# 2\. Download \*\*SFML 2.6.1\*\* matching your Visual Studio version:

# &#x20;  - Visual Studio 2022 → pick `Visual C++ 17 (2022) - 64-bit`

# &#x20;  - Visual Studio 2019 → pick `Visual C++ 15 (2019) - 64-bit`

# 3\. Extract the zip to `C:\\SFML\\`

# 4\. After extracting you should see:

# &#x20;  ```

# &#x20;  C:\\SFML\\include\\

# &#x20;  C:\\SFML\\lib\\

# &#x20;  C:\\SFML\\bin\\

# &#x20;  ```

# 

# \-Open the Project in Visual Studio

# 

# 1\. Open Visual Studio

# 2\. Click \*\*Open a project or solution\*\*

# 3\. Navigate to the project folder and open the `.sln` file

# 

# \-Configure SFML in Visual Studio

# 

# Right-click the \*\*project name\*\* in Solution Explorer → \*\*Properties\*\*

# 

# Make sure the top dropdown says \*\*Debug\*\* and \*\*x64\*\*

# 

# \*\*A) Add Include Directory:\*\*

# ```

# C/C++ → General → Additional Include Directories

# → Add: C:\\SFML\\include

# ```

# 

# \*\*B) Add Library Directory:\*\*

# ```

# Linker → General → Additional Library Directories

# → Add: C:\\SFML\\lib\\Debug

# ```

# 

# \*\*C) Add Library Files:\*\*

# ```

# Linker → Input → Additional Dependencies

# → Add these lines:

# sfml-graphics-d.lib

# sfml-window-d.lib

# sfml-system-d.lib

# sfml-audio-d.lib

# ```

# 

# Click \*\*Apply\*\* then \*\*OK\*\*

# 

# \---

# 

# \### Step 4 — Copy DLL Files

# 

# Copy these files from `C:\\SFML\\bin\\` into your project's `x64\\Debug\\` folder:

# 

# ```

# sfml-graphics-d-2.dll

# sfml-window-d-2.dll

# sfml-system-d-2.dll

# sfml-audio-d-2.dll

# openal32.dll

# ```

# 

# \---

# 

# \### Step 5 — Copy Assets

# 

# Make sure these folders exist next to your `.exe` in `x64\\Debug\\`:

# 

# ```

# x64/Debug/

# &#x20;   Characters/

# &#x20;       Enemies/

# &#x20;           basic\_enemy.png

# &#x20;           fast\_enemy.png

# &#x20;           tank\_enemy.png

# &#x20;           flying\_enemy.png

# &#x20;           boss\_enemy.png

# &#x20;       Towers/

# &#x20;           cannon\_tower.png

# &#x20;           sniper\_tower.png

# &#x20;           machinegun\_tower.png

# &#x20;           slow\_tower.png

# &#x20;           freeze\_tower.png

# &#x20;   background\_music.ogg

# ```

# 

# \-Build and Run

# 

# 1\. Press \*\*Ctrl + Shift + B\*\* to build

# 2\. Press \*\*F5\*\* to run

# 3\. The game will open in fullscreen automatically

# 

# How to Play

# 

# | Action | What it Does |

# |---|---|

# | Press \*\*1\*\* | Select Cannon Tower ($150) |

# | Press \*\*2\*\* | Select Sniper Tower ($200) |

# | Press \*\*3\*\* | Select Machine Gun Tower ($125) |

# | Press \*\*4\*\* | Select Slow Tower ($100) |

# | Press \*\*5\*\* | Select Freeze Tower ($175) |

# | \*\*Left Click\*\* on green tile | Place selected tower |

# | \*\*ESC\*\* | Quit the game |

# 

# \- Waves start automatically with a 3 second countdown

# \- Towers shoot enemies automatically — no manual firing needed

# \- Earn gold when enemies die — spend it on more towers

# \- Lose a life when an enemy reaches the exit

# \- Survive all 5 waves to win

# 

# \-GUI Library Used — SFML 2.6.1

# 

# \*\*SFML (Simple and Fast Multimedia Library)\*\* is a free, open source C++ library

# for graphics, audio, and window management.

# 

# \- Website: \*\*https://sfml-dev.org\*\*

# \- Version used: \*\*SFML 2.6.1\*\*

# \- Download: \*\*https://sfml-dev.org/download.php\*\*

# 

# SFML was chosen because:

# \- It is beginner friendly and well documented

# \- It works directly with C++ without extra setup

# \- It supports graphics, audio, and input in one library

# \- It is widely used in student game projects

# 

# OOP Concepts Used

# 

# | Concept | Where Used |

# |---|---|

# | \*\*Inheritance\*\* | Entity → Enemy → BasicEnemy, FastEnemy, TankEnemy, FlyingEnemy, BossEnemy |

# | \*\*Inheritance\*\* | Entity → Tower → CannonTower, SniperTower, MachineGunTower, SlowTower, FreezeTower |

# | \*\*Polymorphism\*\* | All enemies and towers stored as base class pointers |

# | \*\*Abstract Classes\*\* | Enemy and Tower have pure virtual functions |

# | \*\*Encapsulation\*\* | Private/protected members with getters and setters |

# | \*\*Operator Overloading\*\* | `operator>` in Entity class compares HP values |

# | \*\*Destructors\*\* | Proper cleanup of all dynamically allocated enemies and towers |

# 

# \-Class Hierarchy

# 

# Entity  (abstract base)

# ├── Enemy  (abstract)

# │   ├── BasicEnemy

# │   ├── FastEnemy

# │   ├── TankEnemy

# │   ├── FlyingEnemy

# │   └── BossEnemy

# └── Tower  (abstract)

# &#x20;   ├── CannonTower

# &#x20;   ├── SniperTower

# &#x20;   ├── MachineGunTower

# &#x20;   ├── SlowTower

# &#x20;   └── FreezeTower

# ```

# 

# \-Enemy Types

# 

# | Enemy | HP | Speed | Gold | Special |

# |---|---|---|---|---|

# | Basic | 100 | Medium | 10 | Standard enemy |

# | Fast | 40 | Very Fast | 15 | Hard to hit |

# | Tank | 400 | Very Slow | 30 | Very high HP |

# | Flying | 60 | Fast | 20 | Goes straight to exit |

# | Boss | 800 | Slow | 50 | Regenerates HP over time |

# 

# \-Tower Types

# 

# | Tower | Damage | Range | Cost | Special |

# |---|---|---|---|---|

# | Cannon | 60 | Medium | $150 | High damage, slow fire |

# | Sniper | 100 | Very Long | $200 | Single target, precise |

# | Machine Gun | 12 | Medium | $125 | Rapid fire, low damage |

# | Slow | 5 | Medium | $100 | Slows all enemies in range |

# | Freeze | 20 | Medium | $175 | Freezes target for 1 second |

# 

# Known Issues and Limitations

# 

# \- \*\*No save system\*\* — progress is lost when the game is closed

# \- \*\*No tower upgrade system\*\* — towers cannot be upgraded after placement

# \- \*\*No tower removal\*\* — once a tower is placed it cannot be moved or sold

# \- \*\*Fixed map\*\* — only one map is available, no map selection

# \- \*\*No difficulty selection\*\* — game has one fixed difficulty

# \- \*\*Fullscreen only\*\* — game always opens fullscreen, no windowed mode option

# \- \*\*FlyingEnemy cannot be slowed effectively\*\* — it ignores the path so

# &#x20; slow towers have limited effect on it

# \- \*\*Audio requires OGG format\*\* — MP3 files are not supported by SFML

# \- \*\*Images must be correct size\*\* — very large images need manual scale

# &#x20; adjustment in the constructor of each class

# \- \*\*Font loaded from Windows system folder\*\* — may not work on non-Windows

# &#x20; operating systems

# 

# \-File Structure

# 

# ```

# TowerDefense/

# ├── Entity.h / Entity.cpp

# ├── Enemy.h / Enemy.cpp

# ├── BasicEnemy.h / BasicEnemy.cpp

# ├── FastEnemy.h / FastEnemy.cpp

# ├── TankEnemy.h / TankEnemy.cpp

# ├── FlyingEnemy.h / FlyingEnemy.cpp

# ├── BossEnemy.h / BossEnemy.cpp

# ├── Bullet.h / Bullet.cpp

# ├── Tower.h / Tower.cpp

# ├── CannonTower.h / CannonTower.cpp

# ├── SniperTower.h / SniperTower.cpp

# ├── MachineGunTower.h / MachineGunTower.cpp

# ├── SlowTower.h / SlowTower.cpp

# ├── FreezeTower.h / FreezeTower.cpp

# ├── Map.h / Map.cpp

# ├── Wave.h / Wave.cpp

# ├── UI.h / UI.cpp

# ├── Game.h / Game.cpp

# ├── main.cpp

# └── README.md

# ```

# 

# \-Developer Notes

# 

# \- Built and tested on Windows 11 with Visual Studio 2022

# \- Uses Debug mode only — Release mode not configured

# \- No vectors, structs, or enums used in the codebase

# \- All dynamic memory properly deleted in destructors

# \- Raw arrays used throughout instead of STL containers

