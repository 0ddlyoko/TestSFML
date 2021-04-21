#include "AStar.hpp"

#include <cmath>

using namespace std;

AStar::AStar(Application &app):
        GenericApp(app),
        m_start(1, 1),
        m_end(CELL_COL - 2, CELL_ROW - 20),
        m_found(false),
        m_last_cell(nullptr),
        m_rng((unsigned) std::time(nullptr)),
        m_range(0, 100) {
    for (int y = 0; y < CELL_ROW; y++) {
        for (int x = 0; x < CELL_COL; x++) {
            m_map.push_back(AStarCell({x, y}, 0, 0, m_range(m_rng) <= ASTAR_VOID_PERCENTAGE ? AStarCell::CellType::AIR : AStarCell::CellType::BLOCK));
        }
    }
    m_map.at(getCellIndex(m_start)).setCellType(AStarCell::AIR);
    m_map.at(getCellIndex(m_end)).setCellType(AStarCell::AIR);
}

void AStar::init() {
    m_app.setFps(12000);
    // Add initial position
    AStarCell *initial_cell = &m_map.at(getCellIndex(m_start.x, m_start.y));
    m_cells.emplace(initial_cell, nullptr, distance(initial_cell->getPos(), m_end));
    for (int y = 0; y < CELL_ROW; y++)
        for (int x = 0; x < CELL_COL; x++)
            if (m_map.at(getCellIndex(x, y)).getCellType() == AStarCell::BLOCK)
                setCellColor({x, y}, STONE_COLOR);
}

void AStar::nextIteration() {
    GenericApp::nextIteration();
    setCellColor(m_end, sf::Color::Green);
    setCellColor(m_start, sf::Color::Red);

    if (m_last_cell) {
        // Clear the path
        showPath(m_last_cell, DEFAULT_COLOR);
    }

    if (!m_found) {
        // Perform the next iteration
        if (!m_cells.empty()) {
            // Get and delete the top cell
            Cell current = m_cells.top();
            m_cells.pop();
            // Check for duplicates
            if (!current.m_cell->hasEntered()) {
                // Set that we are doing this cell
                current.m_cell->setEntered(true);
                // Save last cell
                m_last_cell = current.m_cell;
                // Found ?
                if (current.m_cell->getPos() == m_end) {
                    // FOUND !!!!
                    m_found = true;
                } else {
                    // Check for neighbors
                    for (AStarCell *neighbor : getNeighbors(*current.m_cell)) {
                        // Check if we can go to this neighbor
                        if (!canGoTo(*neighbor))
                            continue;
                        // TODO Calculate that
                        double moveCost = cost(*current.m_cell, *neighbor);
                        double newCost = current.m_cell->getCost() + moveCost;
                        double newHeuristic = newCost + distance(neighbor->getPos(), m_end);
                        // Check if we haven't performed this neighbor AND his cost is greater than the new cost
                        if (!neighbor->hasEntered() && (neighbor->getCost() == 0 || neighbor->getCost() > newCost)) {
                            // Update new parent, cost and heuristic
                            neighbor->setParent(current.m_cell);
                            neighbor->setCost(newCost);
                            neighbor->setHeuristic(newHeuristic);
                            // Put this neighbor in the priority queue
                            m_cells.emplace(neighbor, current.m_cell, newHeuristic);
                        }
                    }
                }
            }
        }
    }
    if (m_last_cell)
        showPath(m_last_cell, LINE_COLOR);
    setCellColor(m_start, START_COLOR);
    setCellColor(m_end, END_COLOR);
}

std::vector<AStarCell*> AStar::getNeighbors(const AStarCell &cell) {
    std::vector<AStarCell*> result;
    for (const vec2i &v : NEIGHBORS) {
        const vec2i vector = cell.getPos() + v;
        if (isOutOfBound(vector))
            continue;
        result.push_back(&m_map.at(getCellIndex(vector)));
    }

    return result;
}

void AStar::showPath(AStarCell *cell, sf::Color color) {
    AStarCell *currentCell = cell;
    while (currentCell) {
        setCellColor(currentCell->getPos(), color);
        currentCell = currentCell->getParent();
    }
}

bool AStar::canGoTo(const AStarCell &cell) {
    return cell.getCellType() == AStarCell::AIR;
}

double AStar::cost(const AStarCell &from, const AStarCell &to) {
    // Real distance
    return distance(from.getPos(), to.getPos());
}

double AStar::distance(const vec2i &cell1, const vec2i &cell2) {
    return sqrt(
            pow(cell1.x - cell2.x, 2) +
            pow(cell1.y - cell2.y, 2));
}

// ---------------- Cell ----------------

AStar::Cell::Cell(AStarCell *cell, AStarCell *parent, double heuristic):
        m_cell(cell),
        m_parent(parent),
        m_heuristic(heuristic) {

}

bool operator<(const AStar::Cell &lhs, const AStar::Cell &rhs) {
    return lhs.m_heuristic < rhs.m_heuristic;
}

bool operator>(const AStar::Cell &lhs, const AStar::Cell &rhs) {
    return lhs.m_heuristic > rhs.m_heuristic;
}
