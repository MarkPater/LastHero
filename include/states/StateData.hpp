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
    StateData(std::shared_ptr<GraphicsSettings> gfx_settings,
              std::map<std::string, int> * supported_keys,
              std::stack<State *> * states,
              const std::string & current_path,
              sf::RenderWindow * window);

    std::shared_ptr<GraphicsSettings> gfx_settings();
    std::map<std::string, int> * supported_keys();
    std::stack<State *> * states();
    std::string current_path();

    sf::RenderWindow * window();
    sf::Vector2u max_tile_map_size();

    short grid_size();

private:
    std::shared_ptr<GraphicsSettings> m_gfx_settings;
    std::map<std::string, int> * m_supported_keys;
    std::stack<State *> * m_states;
    std::string m_current_path;
    
    sf::RenderWindow * m_window;
    sf::Vector2u m_max_tile_map_size;

    short m_grid_size;
};

#endif /* STATE_DATA_HPP */