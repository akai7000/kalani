# Kalani Picture Viewer

A fast, lightweight image viewer/organizer built with C++ and SFML.

## Features
- [x] Quick folder/image loading
- [x] Keyboard navigation (arrows for next/prev, etc.)
- [x] Zoom
- [x] Fullscreen mode
- [x] Delete current image by pressing Del
- [ ] Rate images
- [ ] Compare two images

## Build Instructions
1. Open `Kalani.sln` in Visual Studio 2022
2. Ensure SFML is installed and linked (using 3.0.2 now):
   - Download SFML from https://www.sfml-dev.org/
   - Add include/lib paths in project properties (All Configurations)
	 - Add [_SFML root_]`\include` to C/C++ -> General -> Additional Include Directories
	 - Add [_SFML root_]`\lib` to Linker -> General -> Additional Library Directories
   - Link these libraries (add these to Linker -> Input -> Additional Dependencies):
	 - For Debug: `sfml-graphics-d.lib, sfml-window-d.lib, sfml-system-d.lib, sfml-main-d.lib`
	 - For Release: `sfml-graphics.lib, sfml-window.lib, sfml-system.lib, sfml-main.lib`
3. Set C++ language to `ISO C++17 Standard (/std:c++17)`
4. Build & run (F5)

Dependencies: SFML 3.0+

MIT License.