#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include "map/Tile.hpp"
#include <vector>

class TileMap
{
public:
    TileMap();
    ~TileMap();

private:
    unsigned short m_layers;
    unsigned short m_gridSizeU;
    const sf::Vector2u m_maxSize;
    std::vector<std::vector<std::vector<Tile>>> m_map;
    Tile m_mapp[5][5][5];
};

#endif /* TILE_MAP_HPP */