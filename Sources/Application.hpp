#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Keyboard.hpp"
#include "Apps/GenericApp.hpp"

class GenericApp;

constexpr int DEFAULT_FPS{60};

class Application {
public:

    Application(const int width,
                const int height,
                std::string title,
                const std::string& default_font_name = "arial");

    template<typename T>
    void init() {
        m_generic_app = std::make_unique<T>(*this);
        m_fps = DEFAULT_FPS;
        m_generic_app->init();
    }
    void run();
    void display();

    [[nodiscard]] bool isPaused() const;
    void togglePause();
    void pause();
    void resume();
    void nextIteration();

    [[nodiscard]] int getFps() const;
    void setFps(int fps);
    [[nodiscard]] sf::Font &getDefaultFont();
    const sf::Font &getDefaultFont() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    const std::string &getTitle() const;
    [[nodiscard]] sf::RenderWindow &getWindow();
    [[nodiscard]] Keyboard &getKeyboard();
private:
    void pollEvents();

    std::unique_ptr<GenericApp> m_generic_app;
    sf::Font m_default_font;
    int m_width;
    int m_height;
    std::string m_title;
    sf::RenderWindow m_window;
    Keyboard m_keyboard;
    sf::Text m_pause_text;

    int m_fps;
    bool m_paused;
};
