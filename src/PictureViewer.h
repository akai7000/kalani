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
    bool loadCurrentImage();
    const std::vector<std::filesystem::path> getImages() const;
    size_t getCurrentIndex();
    void setCurrentIndex(size_t currentIndex);
    
private:
    sf::RenderWindow& m_window;
    sf::View m_view;
    std::optional<sf::Sprite> m_sprite;
    sf::Texture m_texture;

    std::vector<std::filesystem::path> m_images;
    size_t m_currentIndex = 0;
    bool m_textureLoaded = false;
    float m_zoom = 1.0f;
    sf::Font m_font;

    //void loadImageList(const std::filesystem::path& folder);
    //void centerView();
    void resetView();

    void nextImage();
    void prevImage();
    void zoom(float factor);
    void toggleFullscreen();
    void fitAndCenter();
    void deleteCurrentImage();
};