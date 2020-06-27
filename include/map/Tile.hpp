#ifndef TILE_HPP
#define TILE_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

class Tile
{
public:
    Tile();
    Tile(float x, float y, short grid_size);
    ~Tile();

    void update();
    void render(sf::RenderTarget & target);

    sf::RectangleShape & get_tile();

private:
    float m_x;
    float m_y;
    short m_grid_size;
    sf::RectangleShape m_shape;
};

#endif /* TILE_MAP */