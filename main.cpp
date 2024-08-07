#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include "utils.h"
#include "constants.h"
//#include "ImageFile.h"

using namespace std;

// TODO: do not load an image every time you click arrows, keep them in ram
// TODO: preload images (maybe not need this one)

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    unsigned int defaultWindowWidth = desktop.width - 200;
    unsigned int defaultWindowHeigth = desktop.height - 200;

    sf::RenderWindow window(sf::VideoMode(defaultWindowWidth, defaultWindowHeigth), WINDOW_TITLE);

    string path = "C:\\pics"; // TODO: use current directory
    vector<string> images = {};
    //vector<ImageFile> imageFiles = {};

    for (const auto& entry : filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && is_image_file(entry.path())) {
            cout << "file: " << entry.path() << endl;
            images.push_back(entry.path().string());

            //ImageFile *file = new ImageFile();
            //file->setFilename(entry.path().string());
            //cout << file->getFilename();

            //imageFiles.push_back(*file);
        }
    }

    int current_file = 0;

    //sf::Image image;
    //if (images.size() > 0 && !image.loadFromFile(images[current_file])) {
    //    cout << "Error loading file to Image: " << images[current_file] << endl;
    //}

    sf::Texture texture;
    if (!texture.loadFromFile(images[current_file])) {
        cout << "Error loading file: " << images[current_file] << endl;
    }

    cout << "Image size: (" << texture.getSize().x << "," << texture.getSize().y << ")" << endl;

    //sf::IntRect rect(0, 0, image.getSize().x, image.getSize().y);
    //texture.loadFromImage(image, rect);

    

    //if (images.size() > 0 && !texture.loadFromFile(images[current_file])) {
    //    cout << "Error loading file: " << images[current_file] << endl;
    //}

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition((window.getSize().x - texture.getSize().x) / 2, (window.getSize().y - texture.getSize().y) / 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    if (current_file != images.size() - 1) {
                        current_file++;
                        if (!texture.loadFromFile(images[current_file])) {
                            cout << "Error loading file: " << images[current_file] << endl;
                        }
                        else {
                            cout << "Image size: (" << texture.getSize().x << "," << texture.getSize().y << ")" << endl;
                            sf::IntRect newRect(0, 0, texture.getSize().x, texture.getSize().y);
                            sprite.setTextureRect(newRect);
                            sprite.setPosition((window.getSize().x - texture.getSize().x) / 2, (window.getSize().y - texture.getSize().y) / 2);
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    if (current_file != 0) {
                        current_file--;
                        if (!texture.loadFromFile(images[current_file])) {
                            cout << "Error loading file: " << images[current_file] << endl;
                        }
                        else {
                            cout << "Image size: (" << texture.getSize().x << "," << texture.getSize().y << ")" << endl;
                            sf::IntRect newRect(0, 0, texture.getSize().x, texture.getSize().y);
                            sprite.setTextureRect(newRect);
                            sprite.setPosition((window.getSize().x - texture.getSize().x) / 2, (window.getSize().y - texture.getSize().y) / 2);
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}