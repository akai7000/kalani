#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include "utils.h"
#include "constants.h"
#include "Picture.h"

using namespace std;

// TODO: do not load an image every time you click arrows, keep them in ram
// TODO: preload images (maybe not need this one)

void populateSpritesWithPic(sf::Image image, vector<sf::Texture> & textures, vector<sf::Sprite> & sprites, sf::Vector2u windowSize) {
	sf::IntRect rectTopLeft(0, 0, image.getSize().x / 2, image.getSize().y / 2);
	sf::IntRect rectTopRight(image.getSize().x / 2, 0, image.getSize().x / 2, image.getSize().y / 2);

	sf::Texture textureTopLeft;
	sf::Texture textureTopRight;
	
	textures.push_back(textureTopLeft);
	textures.push_back(textureTopRight);

	textures[0].loadFromImage(image, rectTopLeft);
	textures[1].loadFromImage(image, rectTopRight);

	sf::Sprite spriteTopLeft;
	sf::Sprite spriteTopRight;
	
	sprites.push_back(spriteTopLeft);
	sprites.push_back(spriteTopRight);

	sprites[0].setTexture(textures[0]);
	sprites[1].setTexture(textures[1]);

	sprites[0].setPosition((windowSize.x - image.getSize().x) / 2, (windowSize.y - image.getSize().y) / 2);
	sprites[1].setPosition((windowSize.x - image.getSize().x) / 2 + image.getSize().x / 2, (windowSize.y - image.getSize().y) / 2);
}

void loadImageToSprite(sf::Sprite &sprite, sf::Texture &texture, sf::Vector2u windowSize, Picture pic) {
	//sf::Texture t = *sprite.getTexture();
    if (!texture.loadFromFile(pic.getFilename())) {
        cout << "Error loading file: " << pic.getFilename() << endl;
        return;
    }
    else {
        cout << "Image size: (" << texture.getSize().x << "," << texture.getSize().y << ")" << endl;
        sf::Vector2u imageSize = texture.getSize();
        float scaleFactor = std::min(
            static_cast<float>(windowSize.x) / imageSize.x,
            static_cast<float>(windowSize.y) / imageSize.y
        );
        sprite.setScale(scaleFactor, scaleFactor);
        sprite.setPosition(
            (windowSize.x - imageSize.x * scaleFactor) / 2,
            (windowSize.y - imageSize.y * scaleFactor) / 2
        );
		sprite.setTexture(texture);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <path_to_images>" << endl;
        return 1;
    }

    string path = argv[1];

    // Set up a window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, windowTitle);
    window.setPosition(sf::Vector2i(-11, 0));

    // Load images from the specified directory
    vector<Picture> pics = {};

    for (const auto& entry : filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && is_image_file(entry.path())) {
            cout << "file: " << entry.path() << " | size: " << entry.file_size() << endl;
            Picture* pic = new Picture();
            pic->setFilename(entry.path().string());
            //pic->setWindowSize(window.getSize());
            pics.push_back(*pic);
        }
    }

    cout << "Number of images loaded: " << pics.size() << endl;

    // Load first image from the specified directory
    sf::Texture texture;
    sf::Sprite sprite;
    int current_file = 0;
    loadImageToSprite(sprite, texture, window.getSize(), pics[current_file]);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    sprite.scale(1.1f, 1.1f);  // Zoom in
                else
                    sprite.scale(0.9f, 0.9f);  // Zoom out
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    if (current_file != pics.size() - 1) {
                        current_file++;
                        loadImageToSprite(sprite, texture, window.getSize(), pics[current_file]);
                    }
				}
                else if (event.key.code == sf::Keyboard::Left) {
                    if (current_file != 0) {
                        current_file--;
                        loadImageToSprite(sprite, texture, window.getSize(), pics[current_file]);
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
