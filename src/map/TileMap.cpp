#include "map/TileMap.hpp"
#include "iostream"

TileMap::TileMap()
    : m_grid_size{ 50 }
    , m_layers{ 1 }
    , m_max_size{ sf::Vector2u{ 40, 20 } }
    , m_map{ m_max_size.x, std::vector<std::vector<Tile *>>{ m_max_size.y, std::vector<Tile *>{ m_layers, nullptr }} }
{
    for (int i = 0; i < m_max_size.x; ++i) {
        for (int j = 0; j < m_max_size.y; ++j) {
            for (int k = 0; k < m_layers; ++k) {
                m_map[i][j][k] = new Tile{ i * m_grid_size, j * m_grid_size, m_grid_size };
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

void TileMap::update(sf::Vector2f mouse_pos)
{
    for (const auto & x : m_map) {
        for (const auto & y : x) {
            for (const auto & tile : y) {
                if (tile->get_tile().getGlobalBounds().contains(mouse_pos)) {
                    tile->get_tile().setFillColor(sf::Color(tile->get_tile().getFillColor().r, tile->get_tile().getFillColor().g, tile->get_tile().getFillColor().b, 200));
                    break;
                }
            }
        }
    }
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