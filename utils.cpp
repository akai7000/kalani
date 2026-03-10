#include <iostream>
#include <sstream>
#include <string>
#include "constants.h"
#include "utils.h"

std::string to_lowercase(std::string s) {
    for (char& c : s)
        c = tolower(c);
    return s;
}

bool is_image_file(const std::filesystem::path& path) {
    return imageExtensions.find(to_lowercase(path.extension().string())) != imageExtensions.end();
}

//sf::Sprite sprite_func(sf::Sprite sprite) {
//
//	sf::Image image;
//	if (!image.loadFromFile(R"(P:\AI\woman1.jpg)")) {
//		std::cout << "Error loading file to Image" << std::endl;
//	}
//
//	sf::Texture textureTopLeft;
//	sf::IntRect rectTopLeft(0, 0, image.getSize().x / 2, image.getSize().y / 2);
//	textureTopLeft.loadFromImage(image, rectTopLeft);
//	//sf::Sprite spriteTopLeft;
//	sprite.setTexture(textureTopLeft);
//
//	return sprite;
//}

sf::Sprite populateSpritesWithPic(sf::Vector2u windowSize) {

	sf::Image image;
	if (!image.loadFromFile(R"(P:\AI\woman1.jpg)")) {
		std::cout << "Error loading file to Image" << std::endl;
	}

	std::cout << image.getPixel(100, 100).toInteger() << std:: endl;

	sf::Texture textureTopLeft;
	//sf::Texture textureTopRight;
	std::cout << image.getSize().x << ", " << image.getSize().y << endl;

	sf::IntRect rectTopLeft(0, 0, image.getSize().x / 2, image.getSize().y / 2);
	//sf::IntRect rectTopRight(image.getSize().x / 2, 0, image.getSize().x / 2, image.getSize().y / 2);

	textureTopLeft.loadFromImage(image, rectTopLeft);
	//textureTopRight.loadFromImage(image, rectTopRight);

	std::cout << textureTopLeft.getSize().x << ", " << textureTopLeft.getSize().y << endl;

	sf::Sprite spriteTopLeft;
	spriteTopLeft.setTexture(textureTopLeft);
	//spriteTopLeft.setPosition((windowSize.x - image.getSize().x) / 2, (windowSize.y - image.getSize().y) / 2);


	//sf::Sprite spriteTopRight;
	//spriteTopRight.setTexture(textureTopRight);
	//spriteTopRight.setPosition((windowSize.x - image.getSize().x) / 2 + textureTopRight.getSize().x, (windowSize.y - image.getSize().y) / 2);

	//auto sprites = new vector<sf::Sprite>();

	//sprites->push_back(spriteTopLeft);
	//sprites.push_back(spriteTopRight);

	return spriteTopLeft;
}