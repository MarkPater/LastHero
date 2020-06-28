#include "map/Tile.hpp"
#include <cstdlib>

Tile::Tile()
    : m_x{ 0.f }
    , m_y{ 0.f }
    , m_grid_size{ 0 }
    , m_shape{ sf::Vector2f{ m_grid_size, m_grid_size } }
{
    std::srand(std::time(nullptr));
}

Tile::Tile(float x, float y, short grid_size, sf::Texture & texture, const sf::IntRect & texture_rect)
    : m_x{ x }
    , m_y{ y }
    , m_grid_size{ grid_size }
    , m_shape{ sf::Vector2f{ grid_size, grid_size } }
    , m_texture{ &texture }
{
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(m_x, m_y);
    m_shape.setTexture(m_texture);
    m_shape.setTextureRect(texture_rect);
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