// src/PictureViewer.cpp
#include "PictureViewer.h"
#include <iostream>
#include <algorithm>  // for std::min, std::max (if needed later)

// Supported image extensions
static const std::vector<std::string> imageExtensions = {
    ".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tga"
    // check if these work as well: ".tiff", ".tif", ".webp"
};

PictureViewer::PictureViewer(sf::RenderWindow& window)
    : m_window(window)
    , m_view(window.getDefaultView())
{
    // Optional: Start with a default folder or wait for user input
    loadFolder("C:/Users/admin/Pictures");
}

void PictureViewer::loadFolder(const std::string& folderPath)
{
    std::filesystem::path path(folderPath);
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
        std::cerr << "Invalid folder: " << folderPath << std::endl;
        return;
    }

    m_images.clear();
    m_currentIndex = 0;
    loadImageList(path);

    if (!m_images.empty()) {
        loadCurrentImage();
    }
    else {
        std::cout << "No images found in folder.\n";
        m_textureLoaded = false;
    }
}

void PictureViewer::loadImageList(const std::filesystem::path& folder)
{
    for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if (std::find(imageExtensions.begin(), imageExtensions.end(), ext) != imageExtensions.end()) {
                m_images.push_back(entry.path());
            }
        }
    }

    std::cout << "Found " << m_images.size() << " images.\n";
}

bool PictureViewer::loadCurrentImage()
{
    if (m_images.empty() || m_currentIndex >= m_images.size()) {
        m_textureLoaded = false;
        m_sprite.reset();  // clear the optional
        return false;
    }

    const auto& path = m_images[m_currentIndex];
    if (m_texture.loadFromFile(path.string())) {
        m_sprite.emplace(m_texture);       // construct sprite in-place with texture
        // or: m_sprite = sf::Sprite(m_texture);
        m_sprite->setTexture(m_texture, true);  // reset rect if needed (optional now)

        centerView();
        m_textureLoaded = true;
        std::cout << "Loaded: " << path.filename() << std::endl;
        return true;
    }
    else {
        std::cerr << "Failed to load: " << path << std::endl;
        m_sprite.reset();
        m_textureLoaded = false;
        return false;
    }
}

void PictureViewer::centerView()
{
    if (!m_textureLoaded || !m_sprite.has_value()) return;

    sf::Vector2u texSize = m_texture.getSize();
    sf::Vector2f winSize = sf::Vector2f(m_window.getSize());

    float scaleX = winSize.x / static_cast<float>(texSize.x);
    float scaleY = winSize.y / static_cast<float>(texSize.y);
    float scale = std::min(scaleX, scaleY);

    m_zoom = scale;
    resetView();
}

void PictureViewer::resetView()
{
    sf::Vector2f winSize = sf::Vector2f(m_window.getSize());
    m_view.setSize(winSize);
    m_view.setCenter(winSize / 2.f);
    m_view.zoom(1.0f / m_zoom);
}

void PictureViewer::handleEvent(const sf::Event& event)
{
    // Window closed (most common way to exit)
    if (event.is<sf::Event::Closed>()) {
        m_window.close();
        return;
    }

    // Key pressed
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        switch (key->scancode) {  // prefer scancode for layout-independent keys
        case sf::Keyboard::Scancode::Right:
        case sf::Keyboard::Scancode::D:
            nextImage();
            break;

        case sf::Keyboard::Scancode::Left:
        case sf::Keyboard::Scancode::A:
            prevImage();
            break;

        case sf::Keyboard::Scancode::Equal:     // + key (main keyboard)
        case sf::Keyboard::Scancode::NumpadPlus:       // numpad +
            zoom(1.1f);
            break;

        case sf::Keyboard::Scancode::Hyphen:  // - key (main keyboard)
        case sf::Keyboard::Scancode::NumpadMinus:     // numpad -
            zoom(0.9f);
            break;

        case sf::Keyboard::Scancode::F:
            toggleFullscreen();
            break;

        case sf::Keyboard::Scancode::R:
            resetView();
            break;

        case sf::Keyboard::Scancode::Escape:
            m_window.close();
            break;

        default:
            break;
        }
        return;
    }

    // Mouse wheel zoom
    if (const auto* wheel = event.getIf<sf::Event::MouseWheelScrolled>()) {
        if (wheel->delta > 0) {
            zoom(1.1f);
        }
        else if (wheel->delta < 0) {
            zoom(0.9f);
        }
        return;
    }

    // Handle window resize to update view size
    if (const auto* resized = event.getIf<sf::Event::Resized>()) {
        m_view.setSize(sf::Vector2f(resized->size));

        // Optional: re-center or re-fit the content after resize
        centerView();     // if you have this method
        // or resetView();   // if you want to re-apply the fit/zoom logic
    }
}

void PictureViewer::update(float /*dt*/)
{
    // For future: smooth transitions, loading spinner, etc.  I don't need this for now.
}

void PictureViewer::render(sf::RenderWindow& target)
{
    target.setView(m_view);

    target.clear(sf::Color(35, 35, 35));

    if (m_textureLoaded && m_sprite.has_value()) {  // or just if (m_sprite)
        target.draw(*m_sprite);                     // dereference the optional
    }
    else {
        // placeholder / error message drawing (optional)
    }

    target.setView(target.getDefaultView());
}

void PictureViewer::nextImage()
{
    if (m_images.empty()) return;
    m_currentIndex = (m_currentIndex + 1) % m_images.size();
    loadCurrentImage();
}

void PictureViewer::prevImage()
{
    if (m_images.empty()) return;
    m_currentIndex = (m_currentIndex == 0) ? m_images.size() - 1 : m_currentIndex - 1;
    loadCurrentImage();
}

void PictureViewer::zoom(float factor)
{
    m_zoom *= factor;
    m_view.zoom(factor);
}

void PictureViewer::toggleFullscreen()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    if (m_window.getSize() == desktop.size) {
        // Currently fullscreen  go windowed
        m_window.create(
            sf::VideoMode({ 1280, 720 }),
            "Kalani Picture Viewer",
            sf::State::Windowed
        );
    }
    else {
        // Go fullscreen
        m_window.create(
            desktop,
            "Kalani Picture Viewer",
            sf::State::Fullscreen
        );
    }

    resetView();
}