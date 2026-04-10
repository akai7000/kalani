# Copilot Instructions for Kalani Picture Viewer

## Project Overview
Kalani is a fast, lightweight image viewer/organizer built with C++ and SFML.

## Coding Standards
- **Language**: C++17
- **Graphics Library**: SFML 3.0+
- **Naming Conventions**:
  - Classes: PascalCase (e.g., `PictureViewer`, `PictureDatabase`)
  - Functions: camelCase (e.g., `loadFolder`, `getImages`)
  - Member Variables: m_ prefix + camelCase (e.g., `m_window`, `m_currentIndex`)
  - Local Variables: camelCase (e.g., `imageSize`)
  - Constants: camelCase (e.g., `imageExtensions`)
  - Files: PascalCase for class files (e.g., `PictureViewer.h`, `PictureViewer.cpp`)
- **Code Style**:
  - Use smart pointers where appropriate (e.g., `std::unique_ptr`, `std::optional`)
  - Prefer `std::filesystem` over legacy file APIs
  - Include guards or `#pragma once` for headers
  - Use `const` and `&` for parameters where possible
  - Comments: Use `//` for single-line, `/* */` for multi-line. TODO comments for future work.
- **Project Structure**:
  - `src/`: Source files (.cpp, .h)
  - `external/`: Third-party libraries (e.g., imgui)
  - Root: README.md, project files (.sln, .vcxproj)
- **Dependencies**:
  - SFML 3.0+: Graphics, Window, System
  - ImGui (for future UI features)
- **Build System**: Visual Studio 2022, ISO C++17 Standard

## Guidelines for Code Generation
- Maintain consistency with existing codebase
- Use RAII principles
- Handle errors gracefully (e.g., check file existence before loading)
- For graphics code, follow SFML best practices
- When adding features, update README.md if necessary
- Write unit tests for new functionality using Google Test

## Common Patterns
- Window management: Create window in main, pass reference to viewer classes
- Event handling: Use SFML event loop with `pollEvent`
- Image loading: Check extensions, load with `sf::Texture::loadFromFile`
- Navigation: Circular indexing for next/prev images

This ensures Copilot generates code that fits seamlessly into the project.