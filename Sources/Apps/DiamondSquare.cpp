#include "DiamondSquare.hpp"

#include "../Util/MathUtil.hpp"
#include <chrono>

using namespace std;

using Clock=std::chrono::high_resolution_clock;

DiamondSquare::DiamondSquare(Application &app):
        GenericApp(app, 1025, 1025),
        m_map(m_width * m_height, 0) {
}

void DiamondSquare::init() {
    m_app.setFps(500);
    createNewMap();
    cout << "LifeGame::init()" << endl;
}

void DiamondSquare::update() {
    GenericApp::update();
    if (m_app.getKeyboard().isKeyDown(KEY_NEW_MAP, true)) {
        createNewMap();
    }
}

void DiamondSquare::nextIteration() {
    GenericApp::nextIteration();
}

void DiamondSquare::createNewMap() {
    // Clear the map
    int width = m_width;
    int height = m_height;
    // Initialize corners
    // Top left
    m_map.at(0) = random(DS_MIN_HEIGHT, DS_MAX_HEIGHT);
    // Top right
    m_map.at(getCellIndex(width - 1, 0)) = random(DS_MIN_HEIGHT, DS_MAX_HEIGHT);
    // Bot left
    m_map.at(getCellIndex(0, height - 1)) = random(DS_MIN_HEIGHT, DS_MAX_HEIGHT);
    // Bot right
    m_map.at(getCellIndex(width - 1, height - 1)) = random(DS_MIN_HEIGHT, DS_MAX_HEIGHT);

    // Here comes the program
    int i = width - 1;
    while (i > 1) {
        auto t1 = Clock::now();
        int id = i / 2;
        uniform_int_distribution<int> dist(-id, id);
        for (int x = id; x < width; x += i) {
            for (int y = id; y < height; y += i) {
                double avg = (
                                     getAt(x - id, y - id) +
                                     getAt(x + id, y - id) +
                                     getAt(x - id, y + id) +
                                     getAt(x + id, y + id)
                             ) / 4.0;
                m_map.at(getCellIndex(x, y)) =
                        MathUtil::range(DS_MIN_HEIGHT, DS_MAX_HEIGHT, int(avg + dist(m_mt)));
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
                m_map.at(getCellIndex(x, y)) = int((sum / n) + dist(m_mt));
            }
        }
        auto t2 = Clock::now();
        cout << "Duration for " << i << " is " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms" << endl;
        i = id;
    }

    // Draw
    for (int cellIndex = 0; cellIndex < m_width * m_height; cellIndex++) {
        setCellColor(cellIndex, getColor(m_map.at(cellIndex)));
    }
}

sf::Color DiamondSquare::getColor(int pos) {
    double d = MathUtil::invLerp(DS_MIN_HEIGHT, DS_MAX_HEIGHT, pos);
    int colorIndex = MathUtil::range(0, int(CELL_COLORS_COUNT - 1), int(d * CELL_COLORS_COUNT));
    return CELL_COLORS[colorIndex];
}

int DiamondSquare::getAt(int x, int y) {
    return m_map.at(getCellIndex(x, y));
}
