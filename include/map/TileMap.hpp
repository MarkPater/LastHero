#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include "map/Tile.hpp"
#include <vector>

class TileMap
{
public:
    TileMap();
    ~TileMap();

    void update();
    void render(sf::RenderTarget & target);

private:
    unsigned short m_layers;
    unsigned short m_grid_size_f;
    const sf::Vector2u m_max_size;
    std::vector<std::vector<std::vector<Tile *>>> m_map;
};

#endif /* TILE_MAP_HPP */