#include "states/StateData.hpp"
#include "states/State.hpp"
#include "GraphicsSettings.hpp"

StateData::StateData(sf::RenderWindow * window,
                     std::shared_ptr<GraphicsSettings> gfx_settings,
                     std::map<std::string, int> * supported_keys,
                     std::stack<State *> * states)
    : m_gfx_settings{ std::move(gfx_settings) }
    , m_supported_keys{ supported_keys }
    , m_states{ states }
    , m_window{ window }
    , m_max_tile_map_size{ sf::Vector2u{20, 10} }
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