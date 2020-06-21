#ifndef TILE_HPP
#define TILE_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

class Tile
{
public:
    Tile();
    Tile(float x, float y, unsigned grid_size_u);
    ~Tile();

    void update();
    void render(sf::RenderTarget & target);

    sf::RectangleShape & get_tile();

private:
    float m_x;
    float m_y;
    unsigned m_grid_size_u;
    sf::RectangleShape m_shape;
};

#endif /* TILE_MAP */