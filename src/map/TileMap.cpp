#include "map/TileMap.hpp"

TileMap::TileMap()
    : m_grid_size_f(100.f)
    , m_layers(5)
    , m_max_size(sf::Vector2u(20, 12))
    , m_map(m_max_size.x, std::vector<std::vector<Tile *>>(m_max_size.y, std::vector<Tile *>(m_layers, new Tile())))
{
    for (int i = 0; i < m_max_size.x; ++i) {
        for (int j = 0; j < m_max_size.y; ++j) {
            for (int k = 0; k < m_layers; ++k) {
                m_map[i][j][k] = new Tile(i * m_grid_size_f, j * m_grid_size_f, m_grid_size_f);
            }
        }
    }
}

TileMap::~TileMap()
{
    for (const auto & x : m_map) {
        for (const auto & y : x) {
            for (auto & tile : y) {
                delete tile;
            }
        }
    }
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget & target)
{
    for (const auto & x : m_map) {
        for (const auto & y : x) {
            for (const auto & tile : y) {
                tile->render(target);
            }
        }
    }
}