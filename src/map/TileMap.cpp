#include "map/TileMap.hpp"
#include <iostream>
#include <cassert>

TileMap::TileMap(float grid_size,
                 sf::Vector2u max_size,
                 std::string current_path)
    : m_grid_size{ grid_size }
    , m_layers{ 1 }
    , m_max_size{ max_size }
    , m_map{ m_max_size.x, std::vector<std::vector<Tile *>>{ m_max_size.y, std::vector<Tile *>{ m_layers, nullptr } } }
{
    /*for (int i = 0; i < m_max_size.x; ++i) {
        for (int j = 0; j < m_max_size.y; ++j) {
            for (int k = 0; k < m_layers; ++k) {
                m_map[i][j][k] = new Tile{ i * m_grid_size, j * m_grid_size, m_grid_size };
            }
        }
    }*/
    if (!m_tile_map_texture_sheet.loadFromFile(current_path + "/resources/images/sprites/tiles/tileset.png")) {
        assert(false && "TileMap::TileMap::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

TileMap::~TileMap()
{
    for (const auto & x : m_map) {
        for (const auto & y : x) {
            for (auto tile : y) {
                delete tile;
            }
        }
    }
}

void TileMap::add_tile(short x, short y, short z, const sf::IntRect & tile_rect)
{
    /* Take three indecies from the mouse position in the grid and add a Tile to the position if the internall tilemap array allows it */
    if (x >= 0 && x < m_max_size.x && y >= 0 && y < m_max_size.y && z >= 0 && z < m_layers) {
        if (!m_map[x][y][z]) {
            m_map[x][y][z] = new Tile(x * m_grid_size, y * m_grid_size, m_grid_size, m_tile_map_texture_sheet, tile_rect);
            std::cout << "TileMap::add_tile():\t" << "Added Tile" << "\n";
        }
    }
}

void TileMap::remove_tile(short x, short y, short z)
{
    /* Take three indecies from the mouse position in the grid and remove a Tile at that position if the internall tilemap array allows it */
    if (x >= 0 && x < m_max_size.x && y >= 0 && y < m_max_size.y && z >= 0 && z < m_layers) {
        if (m_map[x][y][z]) {
            delete m_map[x][y][z];
            m_map[x][y][z] = nullptr;
            std::cout << "TileMap::remove_tile():\t" << "Removed Tile" << "\n";
        }
    }
}

void TileMap::update(sf::Vector2f mouse_pos)
{
    for (const auto & x : m_map) {
        for (const auto & y : x) {
            for (const auto tile : y) {
                if (tile) {
                    if (tile->get_tile().getGlobalBounds().contains(mouse_pos)) {
                        tile->get_tile().setFillColor(sf::Color(tile->get_tile().getFillColor().r, tile->get_tile().getFillColor().g, tile->get_tile().getFillColor().b, 200));
                        break;
                    }
                }
            }
        }
    }
}

void TileMap::render(sf::RenderTarget & target)
{
    for (const auto & x : m_map) {
        for (const auto & y : x) {
            for (const auto tile : y) {
                if (tile) {
                    tile->render(target);
                }
            }
        }
    }
}