#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include "utils.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1496, 1496), "Kalani Photo Viewer");

    string path = ".";
    vector<string> images = {};
    for (const auto& entry : filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && is_image_file(entry.path())) {
            cout << "file: " << entry.path() << " | ext: " << entry.path().extension() << endl;
            images.push_back(entry.path().string());
        }
    }

    int current_file = 0;

    sf::Texture texture;
    if (images.size() > 0 && !texture.loadFromFile(images[current_file])) {
        cout << "Error loading file: " << images[current_file] << endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

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
                    }
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    if (current_file != 0) {
                        current_file--;
                        if (!texture.loadFromFile(images[current_file])) {
                            cout << "Error loading file: " << images[current_file] << endl;
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