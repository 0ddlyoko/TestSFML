#pragma once

#include <SFML/System/Vector2.hpp>

class Cell;

class AStarCell {
public:
    enum CellType {
        AIR,
        BLOCK,
    };

    using vec2i = sf::Vector2<int>;

    AStarCell(vec2i &pos, unsigned cost, unsigned heuristic, CellType cell_type);
    AStarCell(vec2i &&pos, unsigned cost, unsigned heuristic, CellType cell_type);

    [[nodiscard]] const vec2i &getPos() const;
    [[nodiscard]] unsigned getCost() const;
    void setCost(unsigned cost);
    [[nodiscard]] unsigned getHeuristic() const;
    void setHeuristic(unsigned heuristic);
    [[nodiscard]] bool hasEntered() const;
    void setEntered(bool entered);
    [[nodiscard]] AStarCell *getParent() const;
    void setParent(AStarCell *parent);
    [[nodiscard]] CellType getCellType() const;
    void setCellType(CellType cell_type);

private:
    vec2i m_pos;
    unsigned m_cost;
    unsigned m_heuristic;
    bool m_entered;
    AStarCell *m_parent;
    CellType m_cell_type;
};



