#include "PictureViewer.h"
#include <iostream>
#include <algorithm>

// Supported image extensions
static const std::vector<std::string> imageExtensions = {
    ".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tga"
    // check if these work as well: ".tiff", ".tif", ".webp"
};

PictureViewer::PictureViewer(sf::RenderWindow& window)
    : m_window(window)
    , m_view(window.getDefaultView())
{
    // Try to load a font (use a path that exists on your system or bundle one)
    // Example: system font on Windows
    if (!m_font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font for placeholder text\n";
        // Optionally set a flag to skip text drawing later
    }

    // Or if you bundle arial.ttf next to the exe:
    // if (!m_font.openFromFile("arial.ttf")) { ... }
}

void PictureViewer::loadFolder(const std::string& folderPath)
{
    std::filesystem::path dir(folderPath);
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        std::cerr << "Invalid folder: " << folderPath << std::endl;
        return;
    }

    m_images.clear();
    m_currentIndex = 0;

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if (std::find(imageExtensions.begin(), imageExtensions.end(), ext) != imageExtensions.end()) {
                m_images.push_back(entry.path());
            }
        }
    }

    //  Should I sort the m_images?

    std::cout << "Found " << m_images.size() << " images in folder.\n";
}

bool PictureViewer::loadCurrentImage()
{
    if (m_images.empty() || m_currentIndex >= m_images.size()) {
        m_textureLoaded = false;
        m_sprite.reset();
        return false;
    }

    const auto& p = m_images[m_currentIndex];
    if (m_texture.loadFromFile(p.string())) {
        m_sprite.emplace(m_texture);
        m_sprite->setTexture(m_texture, true);  // reset rect to full texture

        m_textureLoaded = true;

        fitAndCenter();

        return true;
    }
    else {
        std::cerr << "Failed to load: " << p << std::endl;
        m_textureLoaded = false;
        m_sprite.reset();
        return false;
    }
}

const std::vector<std::filesystem::path> PictureViewer::getImages() const {
    return m_images;
}

size_t PictureViewer::getCurrentIndex() {
    return m_currentIndex;
}

void PictureViewer::setCurrentIndex(size_t currentIndex) {
    m_currentIndex = currentIndex;
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
    if (event.is<sf::Event::Closed>()) {
        m_window.close();
        return;
    }

    // Key pressed
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        switch (key->scancode) {
        case sf::Keyboard::Scancode::Right:
        case sf::Keyboard::Scancode::D:
            nextImage();
            break;

        case sf::Keyboard::Scancode::Left:
        case sf::Keyboard::Scancode::A:
            prevImage();
            break;

        case sf::Keyboard::Scancode::Equal:
        case sf::Keyboard::Scancode::NumpadPlus:
            zoom(1.1f);
            break;

        case sf::Keyboard::Scancode::Hyphen:
        case sf::Keyboard::Scancode::NumpadMinus:
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
        fitAndCenter();
    }
}

void PictureViewer::update(float /*dt*/)
{
    // For future: smooth transitions, loading spinner, etc.  I don't need this for now.
}

void PictureViewer::render(sf::RenderWindow& target)
{
    target.clear(sf::Color(35, 35, 35));

    target.setView(m_view);

    if (m_textureLoaded && m_sprite.has_value()) {
        target.draw(*m_sprite);
    }
    else {
        // Only draw text if font loaded successfully
        if (!m_font.getInfo().family.empty()) {  // simple check: empty if load failed
            sf::Text msg(m_font);  // required: pass font at construction

            msg.setString("No images loaded. Open a folder or file.");
            msg.setCharacterSize(24);
            msg.setFillColor(sf::Color::White);
            msg.setPosition({ 50.f, 50.f });

            target.draw(msg);
        }
        // Optional: draw a simple background rect or icon if font fails
        // e.g. sf::RectangleShape bg(sf::Vector2f(400.f, 100.f));
        // bg.setFillColor(sf::Color(50, 50, 50));
        // bg.setPosition(40.f, 40.f);
        // target.draw(bg);
    }

    target.setView(target.getDefaultView());  // reset for any future HUD
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

void PictureViewer::fitAndCenter()
{
    if (!m_textureLoaded || !m_sprite.has_value()) {
        return;
    }

    sf::Vector2f imageSize = sf::Vector2f(m_texture.getSize());
    sf::Vector2f windowSize = sf::Vector2f(m_window.getSize());

    float scaleX = windowSize.x / imageSize.x;
    float scaleY = windowSize.y / imageSize.y;
    float fitScale = std::min(scaleX, scaleY);

    m_view.setSize(windowSize);
    m_view.setCenter(imageSize / 2.f);
    m_view.setViewport(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f)));

    m_view.zoom(1.f / fitScale);
}