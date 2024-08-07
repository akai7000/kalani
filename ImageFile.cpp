#include "ImageFile.h"

void ImageFile::setFilename(std::string str) {
	filename = str;
}

std::string ImageFile::getFilename() {
	return filename;
}

void ImageFile::setImage(sf::Image img) {
	image = img;
}

sf::Image ImageFile::getImage() {
	return image;
}