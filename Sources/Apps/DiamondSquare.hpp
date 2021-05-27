#pragma once

#include <random>
#include <vector>
#include "GenericApp.hpp"

constexpr int DS_MIN_HEIGHT = -255;
constexpr int DS_MAX_HEIGHT = 255;

class DiamondSquare : public GenericApp {
public:
    static const unsigned CELL_COLORS_COUNT = 18;
    const sf::Color CELL_COLORS[CELL_COLORS_COUNT] = {
            sf::Color(0, 0, 204),
            sf::Color(0, 102, 204),
            sf::Color(0, 204, 204),
            sf::Color(0, 255, 255),
            sf::Color(51, 255, 255),
            sf::Color(102, 255, 255),
            sf::Color(255, 255, 153),
            sf::Color(255, 255, 0),
            sf::Color(153, 255, 153),
            sf::Color(102, 255, 102),
            sf::Color(0, 255, 0),
            sf::Color(0, 204, 0),
            sf::Color(0, 153, 0),
            sf::Color(204, 255, 153),
            sf::Color(229, 255, 204),
            sf::Color(229, 255, 229),
            sf::Color(255, 255, 229),
            sf::Color(255, 255, 255),
    };
    const sf::Color CELL_COLOR = sf::Color::Black;

    explicit DiamondSquare(Application &app);

    void init() override;
    void nextIteration() override;

private:
    [[nodiscard]] sf::Color getColor(int pos);
    [[nodiscard]] int getAt(int x, int y);

    std::vector<int> m_map;
};
