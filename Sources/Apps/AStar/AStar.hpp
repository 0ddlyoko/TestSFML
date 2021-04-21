#pragma once

#include <queue>
#include <random>

#include "../GenericApp.hpp"
#include "AStarCell.hpp"

const sf::Vector2<int> NEIGHBORS[4] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
};

constexpr int ASTAR_VOID_PERCENTAGE = 70;

class AStar : public GenericApp {
public:
    using vec2i = sf::Vector2<int>;
    const sf::Color STONE_COLOR = sf::Color::Black;
    const sf::Color LINE_COLOR = sf::Color::Magenta;
    const sf::Color START_COLOR = sf::Color::Red;
    const sf::Color END_COLOR = sf::Color::Green;

    struct Cell {
        Cell(AStarCell *cell, AStarCell *parent, unsigned heuristic);

        AStarCell *m_cell;
        AStarCell *m_parent;
        unsigned m_heuristic;

        friend bool operator<(const Cell &lhs, const Cell &rhs);
        friend bool operator>(const Cell &lhs, const Cell &rhs);
    };

    AStar(Application &app);

    void init() override;
    void nextIteration() override;

private:

    [[nodiscard]] std::vector<AStarCell*> getNeighbors(const AStarCell &cell);
    [[nodiscard]] bool canGoTo(const AStarCell &cell) const;
    void showPath(AStarCell *cell, sf::Color color);
    [[nodiscard]] static unsigned distance(const vec2i &cell1, const vec2i &cell2);

    std::vector<AStarCell> m_map;
    std::priority_queue<Cell, std::vector<Cell>, std::greater<>> m_cells;
    sf::Vector2<int> m_start;
    sf::Vector2<int> m_end;
    bool m_found;
    AStarCell *m_last_cell;
    std::mt19937 m_rng;
    std::uniform_int_distribution<int> m_range;
};
