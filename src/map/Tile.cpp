#include "map/Tile.hpp"

#include <sstream>

Tile::Tile()
    : m_x{ 0 }
    , m_y{ 0 }
    , m_grid_size{ 0 }
    , m_shape{ sf::Vector2f{ m_grid_size, m_grid_size } }
{
}

Tile::Tile(float x, float y, short grid_size, sf::Texture & texture, const sf::IntRect & texture_rect)
    : m_x{ x }
    , m_y{ y }
    , m_grid_size{ grid_size }
    , m_shape{ sf::Vector2f{ grid_size, grid_size } }
    , m_texture{ &texture }
{
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(m_x * m_grid_size, m_y * m_grid_size);
    m_shape.setTexture(m_texture);
    m_shape.setTextureRect(texture_rect);
}

Tile::~Tile()
{
    
}

const sf::RectangleShape & Tile::get_tile() const
{
    return m_shape;
}

std::string Tile::get_info() const
{
    std::stringstream ss;
    ss << m_x << " " << m_y << " "
       << m_shape.getTextureRect().left << " " << m_shape.getTextureRect().top << "\n";
    
    return ss.str();
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget & target)
{
    target.draw(m_shape);
}