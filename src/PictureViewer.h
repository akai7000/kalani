#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <string>

class PictureViewer {
public:
    explicit PictureViewer(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderWindow& target);
    void loadFolder(const std::string& folderPath);

private:
    sf::RenderWindow& m_window;
    sf::View m_view;
    std::optional<sf::Sprite> m_sprite;
    sf::Texture m_texture;

    std::vector<std::filesystem::path> m_images;
    size_t m_currentIndex = 0;
    bool m_textureLoaded = false;

    float m_zoom = 1.0f;

    void loadImageList(const std::filesystem::path& folder);
    bool loadCurrentImage();
    void centerView();
    void resetView();

    void nextImage();
    void prevImage();
    void zoom(float factor);
    void toggleFullscreen();
};