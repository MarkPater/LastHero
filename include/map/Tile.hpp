#ifndef TILE_HPP
#define TILE_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <string>

class Tile
{
public:
    Tile();
    Tile(float x, float y, short grid_size, sf::Texture & texture, const sf::IntRect & texture_rect);
    ~Tile();

    const sf::RectangleShape & get_tile() const;
    std::string get_info() const;

    void update();
    void render(sf::RenderTarget & target);

private:
    float m_x;
    float m_y;
    short m_grid_size;

    sf::RectangleShape m_shape;
    sf::Texture * m_texture;
};

#endif /* TILE_MAP */