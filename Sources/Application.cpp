#include "Application.hpp"

#include <iostream>
#include <utility>

Application::Application(const int width,
                         const int height,
                         std::string title,
                         const std::string& default_font_name)
                            : m_window{},
                            m_default_font{},
                            m_width{width},
                            m_height{height},
                            m_title{std::move(title)},
                            m_keyboard{},
                            m_fps{DEFAULT_FPS},
                            m_pause_text{"Pause", m_default_font} {
    m_default_font.loadFromFile("../Res/Fonts/" + default_font_name + ".ttf");
    m_pause_text.setFillColor(sf::Color{0, 0, 0, 128});
    sf::FloatRect textRect{m_pause_text.getLocalBounds()};
    m_pause_text.setOrigin(textRect.left + textRect.width / 2.0f,
                           textRect.top + textRect.height / 2.0f);
    m_pause_text.setPosition(float(width) / 2, 20);
}

void Application::run() {
    m_window.create(sf::VideoMode(m_width, m_height, 32), m_title);
    m_window.setKeyRepeatEnabled(false);
    m_window.setVerticalSyncEnabled(false);
    m_window.setFramerateLimit(m_fps);
    pause();
    while (m_window.isOpen()) {
        m_window.clear(sf::Color::White);
        m_generic_app->update();
        if (!m_paused)
            nextIteration();
        m_generic_app->display();
        display();
        m_window.display();
        pollEvents();
    }
}

void Application::display() {
    if (m_paused) {
        m_window.draw(m_pause_text);
    }
}

bool Application::isPaused() const {
    return m_paused;
}

void Application::togglePause() {
    std::cout << m_paused << std::endl;
    if (m_paused)
        resume();
    else
        pause();
}

void Application::pause() {
    m_paused = true;
}

void Application::resume() {
    m_paused = false;
}

void Application::nextIteration() {
    m_generic_app->nextIteration();
}

int Application::getFps() const {
    return m_fps;
}

void Application::setFps(int fps) {
    m_fps = fps;
    m_window.setFramerateLimit(fps);
}

sf::Font &Application::getDefaultFont() {
    return m_default_font;
}

const sf::Font &Application::getDefaultFont() const {
    return m_default_font;
}

int Application::getWidth() const {
    return m_width;
}

int Application::getHeight() const {
    return m_height;
}

const std::string &Application::getTitle() const {
    return m_title;
}

sf::RenderWindow &Application::getWindow() {
    return m_window;
}

Keyboard &Application::getKeyboard() {
    return m_keyboard;
}

void Application::pollEvents() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                m_keyboard.onPress(event.key.code);
                break;
            case sf::Event::KeyReleased:
                m_keyboard.onRelease(event.key.code);
                break;
            default:
                break;
        }
    }
}
