#include "map/Tile.hpp"
#include <cstdlib>

Tile::Tile()
    : m_x{0.f}
    , m_y{0.f}
    , m_grid_size_u{0}
    , m_shape{sf::Vector2f(m_grid_size_u, m_grid_size_u)}
{
    std::srand(std::time(0));
}

Tile::Tile(float x, float y, unsigned grid_size_u)
    : m_x{x}
    , m_y{y}
    , m_grid_size_u{grid_size_u}
    , m_shape{sf::Vector2f(grid_size_u, grid_size_u)}
{
    m_shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    m_shape.setPosition(m_x, m_y);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(3);
}

Tile::~Tile()
{
    
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget & target)
{
    target.draw(m_shape);
}