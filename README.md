# Kalani Picture Viewer

A fast, lightweight image viewer/organizer built with C++ and SFML.

## Features
- Quick folder/image loading
- Keyboard navigation (arrows for next/prev, etc.)
- Zoom
- Fullscreen mode

## Build Instructions
1. Open `Kalani.sln` in Visual Studio 2022
2. Ensure SFML is installed and linked:
   - Download SFML from https://www.sfml-dev.org/
   - Add include/lib paths in project properties (C/C++ → General, Linker → General/Input)
   - Link sfml-graphics-d.lib, sfml-window-d.lib, sfml-system-d.lib (debug) or release versions
3. Build & run (F5)

Dependencies: SFML 2.6+ (graphics, window, system modules)

MIT License.