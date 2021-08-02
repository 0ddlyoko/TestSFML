#include "Keyboard.hpp"

#include <iostream>

using namespace std;

Keyboard::Keyboard(): m_keyboard_event() {
    std::fill(m_keyboard_event.begin(), m_keyboard_event.end(), false);
}

void Keyboard::onPress(sf::Keyboard::Key key) {
    m_keyboard_event[key] = true;
}

void Keyboard::onRelease(sf::Keyboard::Key key) {
    m_keyboard_event[key] = false;
}

bool Keyboard::isKeyDown(sf::Keyboard::Key key) const {
    return m_keyboard_event.at(key);
}

bool Keyboard::isKeyDown(sf::Keyboard::Key key, bool reset) {
    const bool is_key_down = m_keyboard_event.at(key);
    if (reset)
        onRelease(key);
    return is_key_down;
}

