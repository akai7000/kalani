#pragma once
#include <string>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "Picture.h"

//bool is_image_file(const std::filesystem::path& path);

std::string to_lowercase(std::string s);

//sf::Sprite sprite_func(sf::Sprite);

sf::Sprite populateSpritesWithPic(sf::Vector2u);
