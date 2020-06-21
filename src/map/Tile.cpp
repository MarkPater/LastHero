#include "map/Tile.hpp"
#include <cstdlib>

Tile::Tile()
    : m_x{ 0.f }
    , m_y{ 0.f }
    , m_grid_size_u{ 0 }
    , m_shape{ sf::Vector2f(m_grid_size_u, m_grid_size_u) }
{
    std::srand(std::time(nullptr));
}

Tile::Tile(float x, float y, unsigned grid_size_u)
    : m_x{ x }
    , m_y{ y }
    , m_grid_size_u{ grid_size_u }
    , m_shape{sf::Vector2f(grid_size_u, grid_size_u)}
{
    m_shape.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256, 40));
    m_shape.setPosition(m_x, m_y);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(3);
}

Tile::~Tile()
{
    
}

sf::RectangleShape & Tile::get_tile()
{
    return m_shape;
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget & target)
{
    target.draw(m_shape);
}