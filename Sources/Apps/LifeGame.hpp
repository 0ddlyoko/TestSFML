#pragma once

#include <random>
#include <vector>
#include "GenericApp.hpp"

class LifeGame : public GenericApp {
public:
    const sf::Color CELL_COLOR = sf::Color::Black;

    explicit LifeGame(Application &app);

    void init() override;
    void nextIteration() override;

private:
    [[nodiscard]] unsigned getNumberOfCellsAround(int x, int y);

    std::vector<bool> m_map;
    std::uniform_int_distribution<int> m_range;
};
