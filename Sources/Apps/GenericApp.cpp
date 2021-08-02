#include "GenericApp.hpp"

GenericApp::GenericApp(Application& app, int width, int height):
                                        m_width(width),
                                        m_height(height),
                                        m_cell_size_width(float(app.getWidth()) / float(m_width)),
                                        m_cell_size_height(float(app.getHeight()) / float(m_height)),
                                        m_app(app),
                                        m_vertex(),
                                        m_rd(),
                                        m_mt(m_rd()) {
    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++)
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

int GenericApp::getCellIndex(int x, int y) const {
    return y * m_width + x;
}

int GenericApp::getCellIndex(const sf::Vector2<int> vector) const {
    return getCellIndex(vector.x, vector.y);
}

sf::Vector2<int> GenericApp::getCellVector(int index) const {
    return {int(index % m_width), int(index / m_width)};
}

bool GenericApp::isOutOfBound(int x, int y) const {
    return x < 0 || x >= m_width || y < 0 || y >= m_height;
}

bool GenericApp::isOutOfBound(const sf::Vector2<int> vector) const {
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
