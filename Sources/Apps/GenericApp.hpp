#pragma once

#include <random>
#include "../Application.hpp"

class Application;

class GenericApp {

public:
    const sf::Color DEFAULT_COLOR = sf::Color::White;
    const sf::Keyboard::Key KEY_UP = sf::Keyboard::Z;
    const sf::Keyboard::Key KEY_LEFT = sf::Keyboard::Q;
    const sf::Keyboard::Key KEY_DOWN = sf::Keyboard::S;
    const sf::Keyboard::Key KEY_RIGHT = sf::Keyboard::D;
    const sf::Keyboard::Key KEY_PAUSE = sf::Keyboard::Space;
    const sf::Keyboard::Key KEY_NEXT_ITERATION = sf::Keyboard::N;

    explicit GenericApp(Application& app, int width, int height);
    virtual ~GenericApp() = default;

    virtual void init() = 0;
    virtual void nextIteration() = 0;
    virtual void update();

    virtual void display();

    void setCellColor(int x, int y, sf::Color color);
    void setCellColor(sf::Vector2<int> vec, sf::Color color);
    void setCellColor(int index, sf::Color color);
    void resetCellColor(int x, int y);
    void resetCellColor(sf::Vector2<int> vec);
    void resetCellColor(int index);
    [[nodiscard]] int getCellIndex(int x, int y) const;
    [[nodiscard]] int getCellIndex(sf::Vector2<int> vector) const;
    [[nodiscard]] sf::Vector2<int> getCellVector(int index) const;

    [[nodiscard]] bool isOutOfBound(int x, int y) const;
    [[nodiscard]] bool isOutOfBound(sf::Vector2<int> vector) const;
    [[nodiscard]] int random(int min, int max);

protected:
    const int m_width;
    const int m_height;
    const float m_cell_size_width;
    const float m_cell_size_height;
    Application& m_app;
    std::vector<sf::Vertex> m_vertex;
    std::random_device m_rd;
    std::mt19937 m_mt;

private:
    void addCell(int x, int y);
};
