#include "LifeGame.hpp"

using namespace std;

LifeGame::LifeGame(Application &app) :
        GenericApp(app),
        m_map(CELL_ROW * CELL_COL),
        m_rng((unsigned) std::time(nullptr)),
        m_range(0, 1) {
    for (unsigned cellIndex = 0; cellIndex < CELL_COL * CELL_ROW; cellIndex++)
        m_map.push_back(m_range(m_rng));
}

void LifeGame::init() {
    m_app.setFps(500);
    // Draw
    for (unsigned cellIndex = 0; cellIndex < CELL_COL * CELL_ROW; cellIndex++) {
        if (m_map.at(cellIndex))
            setCellColor(cellIndex, CELL_COLOR);
        else
            resetCellColor(cellIndex);
    }
    cout << "LifeGame::init()" << endl;
}

void LifeGame::nextIteration() {
    GenericApp::nextIteration();
    std::vector<bool> newMap;
    for (unsigned cellIndex = 0; cellIndex < CELL_ROW * CELL_COL; cellIndex++) {
        sf::Vector2<int> vec = getCellVector(cellIndex);
        unsigned numberOfCellsAround = getNumberOfCellsAround(vec.x, vec.y);
        bool cell = false;
        bool oldCell = m_map.at(cellIndex);
        if (oldCell) {
            if (numberOfCellsAround == 2 || numberOfCellsAround == 3)
                cell = true;
        } else {
            if (numberOfCellsAround == 3)
                cell = true;
        }
        newMap.push_back(cell);
        // Check if it's different from the previous state
        if (cell != oldCell) {
            // Update the view
            if (cell)
                setCellColor(cellIndex, CELL_COLOR);
            else
                resetCellColor(cellIndex);
        }
    }
    m_map = newMap;
    //cout << "LifeGame::update()" << endl;
}

unsigned LifeGame::getNumberOfCellsAround(int x, int y) {
    int numberOfCells = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            // Check if we are out of bound
            if (!isOutOfBound(x + i, y + j) && m_map.at(getCellIndex(x + i, y + j)))
                numberOfCells++;
        }
    return numberOfCells;
}
