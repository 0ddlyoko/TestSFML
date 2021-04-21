#pragma once

#include <random>
#include <stack>
#include "GenericApp.hpp"

class TestApp : public GenericApp {
public:
    enum Direction {
        UP,
        LEFT,
        DOWN,
        RIGHT
    };

    TestApp(Application& app);

    void init() override;
    void nextIteration() override;
private:
    /**
     * Test if we have to change the direction
     */
    void checkChangeDirection();
    /**
     * Call this method if the player loosed his game
     */
    void loose();

    sf::Vector2<int> getRandomFoodLocation();

    sf::Vector2<int> m_pos;
    sf::Vector2<int> m_pos_food;
    Direction m_direction;
    std::mt19937 m_rng;
    std::uniform_int_distribution<int> m_range;
};
