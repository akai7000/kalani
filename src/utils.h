#pragma once
#include <string>
#include <filesystem>
#include <SFML/Graphics.hpp>

//bool is_image_file(const std::filesystem::path& path);

std::string to_lowercase(std::string s);

//sf::Sprite sprite_func(sf::Sprite);

sf::Sprite populateSpritesWithPic(sf::Vector2u);
