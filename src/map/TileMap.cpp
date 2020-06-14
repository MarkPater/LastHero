#include "map/TileMap.hpp"

TileMap::TileMap()
    : m_gridSizeU(50)
    , m_layers(5)
    , m_maxSize(sf::Vector2u(1000, 1000))
    , m_map(m_maxSize.x, std::vector<std::vector<Tile>>(m_maxSize.y, std::vector<Tile>(m_layers, Tile())))
{
    for (int i = 0; i < m_maxSize.x; ++i) {
        for (int j = 0; j < m_maxSize.y; ++j) {
            for (int k = 0; k < m_layers; ++k) {
                m_map[i][j][k] = Tile();
            }
        }
    }
}

TileMap::~TileMap()
{

}