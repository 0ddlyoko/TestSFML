#include "GenericApp.hpp"

GenericApp::GenericApp(Application& app):
                                        m_app(app),
                                        m_cell_size_width(float(app.getWidth()) / CELL_COL),
                                        m_cell_size_height(float(app.getHeight()) / CELL_ROW),
                                        m_rd(),
                                        m_mt(m_rd()) {
    for (int y = 0; y < CELL_ROW; y++)
        for (int x = 0; x < CELL_COL; x++)
            addCell(x, y);
}

void GenericApp::nextIteration() {

}

void GenericApp::update() {
    if (m_app.getKeyboard().isKeyDown(KEY_PAUSE, true)) {
        m_app.togglePause();
    }
    if (m_app.getKeyboard().isKeyDown(KEY_NEXT_ITERATION, true)) {
        m_app.nextIteration();
    }
}

void GenericApp::display() {
    // Display the grid
    m_app.getWindow().draw(m_vertex.data(), m_vertex.size(), sf::Quads);
}

void GenericApp::setCellColor(int x, int y, const sf::Color color) {
    setCellColor(getCellIndex(x, y), color);
}

void GenericApp::setCellColor(const sf::Vector2<int> vec, const sf::Color color) {
    setCellColor(getCellIndex(vec), color);
}

void GenericApp::setCellColor(int index, const sf::Color color) {
    index *= 4;
    m_vertex[index].color = color;
    m_vertex[index + 1].color = color;
    m_vertex[index + 2].color = color;
    m_vertex[index + 3].color = color;
}

void GenericApp::resetCellColor(int x, int y) {
    setCellColor(x, y, DEFAULT_COLOR);
}

void GenericApp::resetCellColor(const sf::Vector2<int> vec) {
    setCellColor(vec, DEFAULT_COLOR);
}

void GenericApp::resetCellColor(int index) {
    setCellColor(index, DEFAULT_COLOR);
}

int GenericApp::getCellIndex(int x, int y) {
    return y * CELL_COL + x;
}

int GenericApp::getCellIndex(const sf::Vector2<int> vector) {
    return getCellIndex(vector.x, vector.y);
}

sf::Vector2<int> GenericApp::getCellVector(int index) {
    return {int(index % CELL_COL), int(index / CELL_COL)};
}

bool GenericApp::isOutOfBound(int x, int y) {
    return x < 0 || x >= CELL_COL || y < 0 || y >= CELL_ROW;
}

bool GenericApp::isOutOfBound(const sf::Vector2<int> vector) {
    return isOutOfBound(vector.x, vector.y);
}

void GenericApp::addCell(int x, int y) {
    sf::Vertex topLeft;
    sf::Vertex topRight;
    sf::Vertex bottomRight;
    sf::Vertex bottomLeft;

    float pixelX = float(x) * m_cell_size_width;
    float pixelY = float(y) * m_cell_size_height;

    topLeft.position = {pixelX, pixelY};
    topRight.position = {pixelX + m_cell_size_width, pixelY};
    bottomRight.position = {pixelX + m_cell_size_width, pixelY + m_cell_size_height};
    bottomLeft.position = {pixelX, pixelY + m_cell_size_height};

    topLeft.color = DEFAULT_COLOR;
    topRight.color = DEFAULT_COLOR;
    bottomRight.color = DEFAULT_COLOR;
    bottomLeft.color = DEFAULT_COLOR;

    m_vertex.push_back(topLeft);
    m_vertex.push_back(topRight);
    m_vertex.push_back(bottomRight);
    m_vertex.push_back(bottomLeft);
}

int GenericApp::random(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_mt);
}
