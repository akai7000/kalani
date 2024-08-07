#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class ImageFile
{
private:
	string filename;
	sf::Image image;

public:
    void setFilename(string);
	string getFilename();

	void setImage(sf::Image);
	sf::Image getImage();
};
