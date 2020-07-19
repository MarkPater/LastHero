#include "map/TileMap.hpp"

#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

TileMap::TileMap(float grid_size,
                 sf::Vector2u max_size,
                 const std::string & current_path)
    : m_grid_size{ grid_size }
    , m_layers{ 1 }
    , m_max_size{ max_size }
    , m_map{ m_max_size.x, std::vector<std::vector<Tile *>>{ m_max_size.y, std::vector<Tile *>{ m_layers, nullptr } } }
    , m_tile_map_texture_sheet_path{ current_path + "/resources/images/sprites/tiles/tileset.png" }
{
    init_tile_map_texture_sheet(m_tile_map_texture_sheet_path);
}

TileMap::~TileMap()
{
    clear();
}

void TileMap::clear()
{
    for (auto & x : m_map) {
        for (auto & y : x) {
            for (auto tile : y) {
                if (tile) {
                    delete tile;
                    tile = nullptr;
                }
            }
            y.clear();
        }
        x.clear();
    }
    m_map.clear();
}

void TileMap::init_tile_map_texture_sheet(const std::string & current_path)
{
    if (!m_tile_map_texture_sheet.loadFromFile(current_path)) {
        assert(false && "TileMap::TileMap::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void TileMap::add_tile(short x, short y, short z, const sf::IntRect & tile_rect)
{
    /* Take three indecies from the mouse position in the grid and add a Tile to the position if the internall tilemap array allows it */
    if (x >= 0 && x < m_max_size.x && y >= 0 && y < m_max_size.y && z >= 0 && z < m_layers) {
        if (!m_map[x][y][z]) {
            m_map[x][y][z] = new Tile(x, y, m_grid_size, m_tile_map_texture_sheet, tile_rect);
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

void TileMap::save_to_file(const std::string & path_to_saving)
{
    std::ofstream ofs{ path_to_saving, std::ios_base::trunc };

    if (ofs.is_open()) {
        ofs << get_info();

        for (const auto & x : m_map) {
            for (const auto & y : x) {
                for (const auto tile : y) {
                    if (tile) {
                        ofs << tile->get_info();
                    }
                }
            }
        }

        ofs.close();
    }
}

void TileMap::load_from_file(const std::string & path_to_loading)
{
    std::ifstream ifs{ path_to_loading };

    if (ifs.is_open()) {
        ifs >> m_grid_size >> m_max_size.x >> m_max_size.y >> m_tile_map_texture_sheet_path;
        init_tile_map_texture_sheet(m_tile_map_texture_sheet_path);

        clear();
        m_map = { m_max_size.x, std::vector<std::vector<Tile *>>{ m_max_size.y, std::vector<Tile *>{ m_layers, nullptr } } };

        float pos_x{}, pos_y{}, texture_x{}, texture_y{};
        while (ifs >> pos_x >> pos_y >> texture_x >> texture_y) {
            add_tile(pos_x, pos_y, 0, sf::IntRect{ texture_x, texture_y, m_grid_size, m_grid_size });
        }

        ifs.close();
    }
}

/// Returns size of grid, maximum map size(width and height) and the path of the texture which used for render
std::string TileMap::get_info() const
{
    std::stringstream ss;
    ss << m_grid_size << "\n"
       << m_max_size.x << " " << m_max_size.y << "\n"
       << m_tile_map_texture_sheet_path << "\n";
    
    return ss.str();
}

const sf::Texture * TileMap::tile_map_texture_sheet() const
{
    return &m_tile_map_texture_sheet;
}

void TileMap::update(sf::Vector2f mouse_pos)
{
    for (const auto & x : m_map) {
        for (const auto & y : x) {
            for (const auto tile : y) {
                if (tile) {
                    if (tile->get_tile().getGlobalBounds().contains(mouse_pos)) {
                        // Do something
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