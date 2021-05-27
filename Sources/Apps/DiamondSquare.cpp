#include "DiamondSquare.hpp"

#include "../Util/MathUtil.hpp"

using namespace std;

DiamondSquare::DiamondSquare(Application &app):
        GenericApp(app),
        m_map(CELL_COL * CELL_ROW, 0) {
    /*
    for (unsigned cellIndex = 0; cellIndex < CELL_COL * CELL_ROW; cellIndex++)
        m_map.push_back(m_range(m_rng));
    */
}

void DiamondSquare::init() {
    m_app.setFps(500);
    int width = CELL_COL;
    int height = CELL_ROW;
    // Initialize corners
    // Top left
    m_map.at(0) = MathUtil::random(DS_MIN_HEIGHT, DS_MAX_HEIGHT);
    // Top right
    m_map.at(getCellIndex(width - 1, 0)) = MathUtil::random(DS_MIN_HEIGHT, DS_MAX_HEIGHT);
    // Bot left
    m_map.at(getCellIndex(0, height - 1)) = MathUtil::random(DS_MIN_HEIGHT, DS_MAX_HEIGHT);
    // Bot right
    m_map.at(getCellIndex(width - 1, height - 1)) = MathUtil::random(DS_MIN_HEIGHT, DS_MAX_HEIGHT);

    // Here comes the program
    int i = width - 1;
    while (i > 1) {
        int id = i / 2;
        for (int x = id; x < width; x += i) {
            for (int y = id; y < height; y += i) {
                double avg = (
                        getAt(x - id, y - id) +
                        getAt(x + id, y - id) +
                        getAt(x - id, y + id) +
                        getAt(x + id, y + id)
                        ) / 4.0;
                m_map.at(getCellIndex(x, y)) =
                        MathUtil::range(DS_MIN_HEIGHT, DS_MAX_HEIGHT, int(avg + MathUtil::random(-id, id)));
            }
        }
        int decal = 0;
        for (int x = 0; x < width; x += id) {
            if (decal == 0)
                decal = id;
            else
                decal = 0;
            for (int y = decal; y < width; y += i) {
                int sum = 0;
                int n = 0;
                if (x >= id) {
                    sum += m_map.at(getCellIndex(x - id, y));
                    n++;
                }
                if (x + id < width) {
                    sum += m_map.at(getCellIndex(x + id, y));
                    n++;
                }
                if (y >= id) {
                    sum += m_map.at(getCellIndex(x, y - id));
                    n++;
                }
                if (y + id < width) {
                    sum += m_map.at(getCellIndex(x, y + id));
                    n++;
                }
                m_map.at(getCellIndex(x, y)) = int((sum / n) + MathUtil::random(-id, id));
            }
        }
        i = id;
    }

    // Draw
    for (int cellIndex = 0; cellIndex < CELL_COL * CELL_ROW; cellIndex++) {
        setCellColor(cellIndex, getColor(m_map.at(cellIndex)));
        /*
        if (m_map.at(cellIndex))
            setCellColor(cellIndex, CELL_COLOR);
        else
            resetCellColor(cellIndex);
        */
    }
    cout << "LifeGame::init()" << endl;
}

void DiamondSquare::nextIteration() {
    GenericApp::nextIteration();
}

sf::Color DiamondSquare::getColor(int pos) {
    double d = MathUtil::invLerp(DS_MIN_HEIGHT, DS_MAX_HEIGHT, pos);
    int colorIndex = MathUtil::range(0, int(CELL_COLORS_COUNT - 1), int(d * CELL_COLORS_COUNT));
    return CELL_COLORS[colorIndex];
}

int DiamondSquare::getAt(int x, int y) {
    return m_map.at(getCellIndex(x, y));
}
