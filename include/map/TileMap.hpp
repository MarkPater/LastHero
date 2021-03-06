#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include "map/Tile.hpp"
#include <vector>

class TileMap
{
public:
    TileMap(float grid_size, sf::Vector2u max_size);
    ~TileMap();

    void add_tile(short x, short y, short z);
    void remove_tile(short x, short y, short z);

    void update(sf::Vector2f mouse_pos);
    void render(sf::RenderTarget & target);

private:
    float m_grid_size;
    short m_layers;
    const sf::Vector2u m_max_size;
    std::vector<std::vector<std::vector<Tile *>>> m_map;
};

#endif /* TILE_MAP_HPP */