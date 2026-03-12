#include <SFML/Graphics.hpp>
#include "PictureViewer.h"

//#include <iostream>
//#include <filesystem>
//#include <vector>
//#include "utils.h"
#include "constants.h"
//#include "Picture.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), windowTitle); // this is for now.  I will be able to resize the window.
    window.setFramerateLimit(144); // change to 60 maybe
    window.setKeyRepeatEnabled(false);   // I think it should be fine without this.  I actually would want the user to hold the key and have very fast browsing.
    PictureViewer viewer(window);

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

//int main(int argc, char* argv[])
//{
//    if (argc < 2) {
//        cout << "Usage: " << argv[0] << " <path_to_images>" << endl;
//        return 1;
//    }
//
//    string path = argv[1];
