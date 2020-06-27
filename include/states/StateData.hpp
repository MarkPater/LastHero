#ifndef STATE_DATA_HPP
#define STATE_DATA_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <memory>
#include <string>
#include <stack>
#include <map>

class GraphicsSettings;
class State;

struct StateData
{
public:
    StateData(sf::RenderWindow * window,
              std::shared_ptr<GraphicsSettings> gfx_settings,
              std::map<std::string, int> * supported_keys,
              std::stack<State *> * states);

    sf::RenderWindow * window();
    std::shared_ptr<GraphicsSettings> gfx_settings();
    std::map<std::string, int> * supported_keys();
    std::stack<State *> * states();

private:
    sf::RenderWindow * m_window;
    std::shared_ptr<GraphicsSettings> m_gfx_settings;
    std::map<std::string, int> * m_supported_keys;
    std::stack<State *> * m_states;
};

#endif /* STATE_DATA_HPP */