#include <SFML/Graphics.hpp>
#include "PictureViewer.h"

#include <iostream>
#include "constants.h"

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), windowTitle); // this is for now.  I will be able to resize the window.
    window.setFramerateLimit(144); // change to 60 maybe
    //window.setKeyRepeatEnabled(false);   // I think it should be fine without this.  I actually would want the user to hold the key and have very fast browsing.
    PictureViewer viewer(window);

    std::string path;
    if (argc >= 2) {
        path = argv[1];

        // Clean up quotes if Windows wraps path in ""
        if (!path.empty() && path.front() == '"' && path.back() == '"') {
            path = path.substr(1, path.size() - 2);
        }

        std::cout << "Opening file from command line: " << path << std::endl;

        // for now just loading the folder
        viewer.loadFolder(std::filesystem::path(path).parent_path().string());
        // but later I need to diaply the actual file that was opened, but then still load the folder
        // ?? viewer.loadSingleImage(path);
    }
    else {
        // No file given --> maybe load last used folder, or prompt, or show welcome screen
        // viewer.loadFolder("C:/Pictures");  // or empty state
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event) {
                viewer.handleEvent(*event);
            }
        }

        float dt = clock.restart().asSeconds();
        viewer.update(dt);
        viewer.render(window);
        window.display();
    }
}
