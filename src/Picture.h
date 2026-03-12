#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Picture
{
private:
	string filename;
	sf::Image image;
	//sf::Vector2u windowSize;

public:
    void setFilename(string);
	string getFilename();

	void setImage(sf::Image);
	sf::Image getImage();

	//void setWindowSize(sf::Vector2u);
};
