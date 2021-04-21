#pragma once

#include <array>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class Keyboard {
public:

    Keyboard();

    void onPress(sf::Keyboard::Key key);

    void onRelease(sf::Keyboard::Key key);

    [[nodiscard]] bool isKeyDown(sf::Keyboard::Key key) const;

    /**
     * Check if the specific key is pressed<br />
     * If reset is set to true, call <i>onRelease(key)</i>
     *
     * @param key The key to check
     * @param reset Reset the state of the key
     * @return <b>true</b> if the given key has been pressed
     */
    [[nodiscard]] bool isKeyDown(sf::Keyboard::Key key, bool reset = false);

private:
    std::array<bool, sf::Keyboard::KeyCount> m_keyboard_event;
};



