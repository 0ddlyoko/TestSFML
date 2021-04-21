#include "AStarCell.hpp"

AStarCell::AStarCell(vec2i &pos, unsigned cost, unsigned heuristic):
        m_pos(pos),
        m_cost(cost),
        m_heuristic(heuristic),
        m_entered(false),
        m_parent(nullptr) {
}

AStarCell::AStarCell(vec2i &&pos, unsigned cost, unsigned heuristic):
        AStarCell(pos, cost, heuristic) {
}

const AStarCell::vec2i &AStarCell::getPos() const {
    return m_pos;
}

unsigned AStarCell::getCost() const {
    return m_cost;
}

void AStarCell::setCost(unsigned int cost) {
    m_cost = cost;
}

unsigned AStarCell::getHeuristic() const {
    return m_heuristic;
}

void AStarCell::setHeuristic(unsigned int heuristic) {
    m_heuristic = heuristic;
}

bool AStarCell::hasEntered() const {
    return m_entered;
}

void AStarCell::setEntered(bool entered) {
    m_entered = entered;
}

AStarCell *AStarCell::getParent() const {
    return m_parent;
}

void AStarCell::setParent(AStarCell *parent) {
    m_parent = parent;
}
