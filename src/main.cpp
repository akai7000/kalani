#include <SFML/Graphics.hpp>
#include "PictureViewer.h"

#include <iostream>
#include <string_view>
#include "constants.h"

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), windowTitle); // this is for now.  I will be able to resize the window.
    window.setFramerateLimit(144); // change to 60 maybe
    //window.setKeyRepeatEnabled(false);   // I think it should be fine without this.  I actually would want the user to hold the key and have very fast browsing.
    PictureViewer viewer(window);

    std::vector<std::string_view> args(argv, argv + argc);

    if (args.size() >= 2)
    {
        std::string_view pathSv = args[1];

        // Remove quotes if present
        if (pathSv.size() >= 2 && pathSv.front() == '"' && pathSv.back() == '"')
        {
            pathSv = pathSv.substr(1, pathSv.size() - 2);
        }

        // Convert to filesystem::path for checks
        std::filesystem::path path(pathSv);

        if (std::filesystem::exists(path))
        {
            if (std::filesystem::is_directory(path))
            {
                // Argument is a folder --> load it, display first image
                viewer.loadFolder(path.string());
                std::cout << "Loaded folder: " << pathSv << " (showing first image)\n";
            }
            else if (std::filesystem::is_regular_file(path))
            {
                std::string parentDir = path.parent_path().string();
                viewer.loadFolder(parentDir);  // now only fills list + index=0, no load

                const auto& images = viewer.getImages();

                auto it = std::find_if(images.begin(), images.end(),
                    [&path](const auto& imgPath) {
                        return imgPath.lexically_normal() == path.lexically_normal();
                    });

                if (it != images.end())
                {
                    viewer.setCurrentIndex(std::distance(images.begin(), it));
                }
                else
                {
                    viewer.setCurrentIndex(0);
                }

                viewer.loadCurrentImage();
            }
            else
            {
                std::cerr << "Invalid path (not file or folder): " << pathSv << "\n";
            }
        }
        else
        {
            std::cerr << "Path does not exist: " << pathSv << "\n";
        }
    }
    else
    {
        // No argument --> optional default behavior
        std::cout << "No path provided. Starting empty.\n";
        // viewer.loadFolder("C:/Default/Pictures");  // should I?
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
