#include "TestApp.hpp"

using namespace std;



TestApp::TestApp(Application& app):
                                  GenericApp(app, 20, 20),
                                  m_pos(m_width / 2, m_height / 2),
                                  m_direction(UP),
                                  m_range(0, m_width * m_height) {
}

void TestApp::init() {
    m_app.setFps(10);
    m_pos_food = getRandomFoodLocation();
    cout << "TestApp::init()" << endl;
}

void TestApp::nextIteration() {
    GenericApp::nextIteration();
    // Check if the direction has been changed
    checkChangeDirection();
    // Check if we are outside of bound
    sf::Vector2<int> oldPos = {m_pos.x, m_pos.y};
    if (m_direction == UP)
        m_pos.y--;
    else if (m_direction == LEFT)
        m_pos.x--;
    else if (m_direction == DOWN)
        m_pos.y++;
    else if (m_direction == RIGHT)
        m_pos.x++;
    // Check if player has lost the game
    if (m_pos.x < 0 || m_pos.x >= m_width || m_pos.y < 0 || m_pos.y >= m_height) {
        loose();
        return;
    }
    // Check if position is the same as the food
    if (m_pos == m_pos_food) {
        // Put the food somewhere on the map
        m_pos_food = getRandomFoodLocation();
    }
    // Reset old position color
    resetCellColor(oldPos.x, oldPos.y);
    // Set in red where the player is
    setCellColor(m_pos.x, m_pos.y, sf::Color::Red);
    // Display the queue of the player

    // Set in green where the food is
    setCellColor(m_pos_food.x, m_pos_food.y, sf::Color::Blue);
}

void TestApp::checkChangeDirection() {
    if (m_direction == UP || m_direction == DOWN) {
        if (m_app.getKeyboard().isKeyDown(KEY_LEFT))
            m_direction = LEFT;
        else if (m_app.getKeyboard().isKeyDown(KEY_RIGHT))
            m_direction = RIGHT;
    } else if (m_direction == LEFT || m_direction == RIGHT) {
        if (m_app.getKeyboard().isKeyDown(KEY_UP))
            m_direction = UP;
        else if (m_app.getKeyboard().isKeyDown(KEY_DOWN))
            m_direction = DOWN;
    }
}

void TestApp::loose() {
    m_app.pause();
    std::cout << "Failed ! " << std::endl;
}

sf::Vector2<int> TestApp::getRandomFoodLocation() {
    // Skip one
    sf::Vector2<int> vec = getCellVector(m_range(m_mt));
    while (vec == m_pos) {
        // If cell is where the player is, choose another one
        vec = getCellVector(m_range(m_mt));
    }
    return vec;
}
