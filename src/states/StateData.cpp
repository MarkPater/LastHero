#include "states/StateData.hpp"
#include "states/State.hpp"
#include "GraphicsSettings.hpp"

StateData::StateData(sf::RenderWindow * window,
                     std::shared_ptr<GraphicsSettings> gfx_settings,
                     std::map<std::string, int> * supported_keys,
                     std::stack<State *> * states)
    : m_window{ window }
    , m_gfx_settings{ std::move(gfx_settings) }
    , m_supported_keys{ supported_keys }
    , m_states{ states }
{
}

sf::RenderWindow * StateData::window()
{
    return m_window;
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
