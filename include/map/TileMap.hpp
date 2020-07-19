#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include "map/Tile.hpp"

#include <vector>
#include <string>

class TileMap
{
public:
    TileMap(float grid_size,
            sf::Vector2u max_size,
            const std::string & current_path);
    ~TileMap();
    
    void clear();
    void init_tile_map_texture_sheet(const std::string & current_path);
    void add_tile(short x, short y, short z, const sf::IntRect & tile_rect);
    void remove_tile(short x, short y, short z);
    void save_to_file(const std::string & path_to_saving);
    void load_from_file(const std::string & path_to_loading);

    std::string get_info() const;
    const sf::Texture * tile_map_texture_sheet() const;

    void update(sf::Vector2f mouse_pos);
    void render(sf::RenderTarget & target);

private:
    float m_grid_size;
    short m_layers;
    
    sf::Vector2u m_max_size;
    sf::Texture m_tile_map_texture_sheet;

    std::vector<std::vector<std::vector<Tile *>>> m_map;
    std::string m_tile_map_texture_sheet_path;
};

#endif /* TILE_MAP_HPP */