#include "Picture.h"

void Picture::setFilename(std::string str) {
	filename = str;
}

std::string Picture::getFilename() {
	return filename;
}

void Picture::setImage(sf::Image img) {
	image = img;
}

sf::Image Picture::getImage() {
	return image;
}

//void Picture::setWindowSize(sf::Vector2u size) {
//	windowSize = size;
//}

//vector<sf::Sprite> Picture::getAllSprites() {
	//sf::Texture textureTopLeft;
	//sf::Texture textureTopRight;
	//sf::IntRect rectTopLeft(0, 0, image.getSize().x / 2, image.getSize().y / 2);
	//sf::IntRect rectTopRight(image.getSize().x / 2, 0, image.getSize().x / 2, image.getSize().y / 2);

	//textureTopLeft.loadFromImage(image, rectTopLeft);
	//textureTopRight.loadFromImage(image, rectTopRight);

	//sf::Sprite spriteTopLeft;
	//spriteTopLeft.setTexture(textureTopLeft);
	//spriteTopLeft.setPosition((windowSize.x - image.getSize().x) / 2, (windowSize.y - image.getSize().y) / 2);

	//sf::Sprite spriteTopRight;
	//spriteTopRight.setTexture(textureTopRight);
	//spriteTopRight.setPosition((windowSize.x - image.getSize().x) / 2 + textureTopRight.getSize().x, (windowSize.y - image.getSize().y) / 2);

	//return sprites;
//}