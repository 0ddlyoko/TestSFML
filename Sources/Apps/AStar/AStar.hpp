#pragma once

#include <queue>
#include "../GenericApp.hpp"
#include "AStarCell.hpp"

const sf::Vector2<int> NEIGHBORS[4] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
};

class AStar : public GenericApp {
public:
    using vec2i = sf::Vector2<int>;

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

    [[nodiscard]] static unsigned distance(const vec2i &cell1, const vec2i &cell2);

private:
    [[nodiscard]] std::vector<AStarCell*> getNeighbors(const AStarCell &cell);

    std::vector<AStarCell> m_map;
    std::priority_queue<Cell, std::vector<Cell>, std::greater<>> m_cells;
    sf::Vector2<int> m_start;
    sf::Vector2<int> m_end;
    bool m_found;
};
