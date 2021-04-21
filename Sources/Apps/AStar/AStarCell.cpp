#include "AStarCell.hpp"

AStarCell::AStarCell(vec2i &pos, unsigned cost, unsigned heuristic, CellType cell_type):
        m_pos(pos),
        m_cost(cost),
        m_heuristic(heuristic),
        m_entered(false),
        m_parent(nullptr),
        m_cell_type(cell_type) {
}

AStarCell::AStarCell(vec2i &&pos, unsigned cost, unsigned heuristic, CellType cell_type):
        AStarCell(pos, cost, heuristic, cell_type) {
}

const AStarCell::vec2i &AStarCell::getPos() const {
    return m_pos;
}

double AStarCell::getCost() const {
    return m_cost;
}

void AStarCell::setCost(double cost) {
    m_cost = cost;
}

double AStarCell::getHeuristic() const {
    return m_heuristic;
}

void AStarCell::setHeuristic(double heuristic) {
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

AStarCell::CellType AStarCell::getCellType() const {
    return m_cell_type;
}

void AStarCell::setCellType(AStarCell::CellType cell_type) {
    m_cell_type = cell_type;
}
