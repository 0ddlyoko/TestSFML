#pragma once

#include <SFML/System/Vector2.hpp>

class Cell;

class AStarCell {
public:
    using vec2i = sf::Vector2<int>;

    AStarCell(vec2i &pos, unsigned cost, unsigned heuristic);
    AStarCell(vec2i &&pos, unsigned cost, unsigned heuristic);

    [[nodiscard]] const vec2i &getPos() const;
    [[nodiscard]] unsigned getCost() const;
    void setCost(unsigned cost);
    [[nodiscard]] unsigned getHeuristic() const;
    void setHeuristic(unsigned heuristic);
    [[nodiscard]] bool hasEntered() const;
    void setEntered(bool entered);
    [[nodiscard]] AStarCell *getParent() const;
    void setParent(AStarCell *parent);

private:
    vec2i m_pos;
    unsigned m_cost;
    unsigned m_heuristic;
    bool m_entered;
    AStarCell *m_parent;
};



