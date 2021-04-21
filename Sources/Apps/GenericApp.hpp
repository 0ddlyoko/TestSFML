#pragma once

#include "../Application.hpp"

class Application;

constexpr int CELL_COL = 100;
constexpr int CELL_ROW = 100;

class GenericApp {

public:
    const sf::Color DEFAULT_COLOR = sf::Color::White;
    const sf::Keyboard::Key KEY_UP = sf::Keyboard::Z;
    const sf::Keyboard::Key KEY_LEFT = sf::Keyboard::Q;
    const sf::Keyboard::Key KEY_DOWN = sf::Keyboard::S;
    const sf::Keyboard::Key KEY_RIGHT = sf::Keyboard::D;
    const sf::Keyboard::Key KEY_PAUSE = sf::Keyboard::Space;
    const sf::Keyboard::Key KEY_NEXT_ITERATION = sf::Keyboard::N;

    GenericApp(Application& app);
    virtual ~GenericApp() = default;

    virtual void init() = 0;
    virtual void nextIteration() = 0;
    void update();

    virtual void display();

    void setCellColor(int x, int y, const sf::Color color);
    void setCellColor(const sf::Vector2<int> vec, const sf::Color color);
    void setCellColor(int index, const sf::Color color);
    void resetCellColor(int x, int y);
    void resetCellColor(const sf::Vector2<int> vec);
    void resetCellColor(int index);
    [[nodiscard]] static int getCellIndex(int x, int y);
    [[nodiscard]] static int getCellIndex(const sf::Vector2<int> vector);
    [[nodiscard]] static sf::Vector2<int> getCellVector(int index);

    [[nodiscard]] static bool isOutOfBound(int x, int y);
    [[nodiscard]] static bool isOutOfBound(const sf::Vector2<int> vector);

protected:
    Application& m_app;
    std::vector<sf::Vertex> m_vertex;
    float m_cell_size_width;
    float m_cell_size_height;

private:
    void addCell(int x, int y);
};
