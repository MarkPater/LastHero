#include "states/StateData.hpp"
#include "states/State.hpp"
#include "GraphicsSettings.hpp"

StateData::StateData(std::shared_ptr<GraphicsSettings> gfx_settings,
                     std::map<std::string, int> * supported_keys,
                     std::stack<State *> * states,
                     const std::string & current_path,
                     sf::RenderWindow * window)
    : m_gfx_settings{ std::move(gfx_settings) }
    , m_supported_keys{ supported_keys }
    , m_states{ states }
    , m_current_path{ current_path }
    , m_window{ window }
    , m_max_tile_map_size{ sf::Vector2u{ 20, 14 } }
    , m_grid_size{ 100 }
{
}

std::shared_ptr<GraphicsSettings> StateData::gfx_settings()
{
    return m_gfx_settings;
}

std::map<std::string, int> * StateData::supported_keys()
{
    return m_supported_keys;
}

std::stack<State *> * StateData::states()
{
    return m_states;
}

std::string StateData::current_path()
{
    return m_current_path;
}

sf::RenderWindow * StateData::window()
{
    return m_window;
}

sf::Vector2u StateData::max_tile_map_size()
{
    return m_max_tile_map_size;
}

short StateData::grid_size()
{
    return m_grid_size;
}