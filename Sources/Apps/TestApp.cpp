#include "TestApp.hpp"

using namespace std;



TestApp::TestApp(Application& app):
                                  GenericApp(app),
                                  m_pos(CELL_COL / 2, CELL_ROW / 2),
                                  m_direction(UP),
                                  m_rng((unsigned) std::time(nullptr)),
                                  m_range(0, CELL_COL * CELL_ROW) {
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
    //cout << m_pos.x << ";" << m_pos.y << endl;
    // Check if player has loose the game
    if (m_pos.x < 0 || m_pos.x >= CELL_COL || m_pos.y < 0 || m_pos.y >= CELL_ROW) {
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
    m_range(m_rng);
    sf::Vector2<int> vec = getCellVector(m_range(m_rng));
    while (vec == m_pos) {
        // If cell is where the player is, choose another one
        vec = getCellVector(m_range(m_rng));
    }
    return vec;
}
