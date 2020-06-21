#ifndef GAME_HPP
#define GAME_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <memory>
#include <string>
#include <stack>
#include <map>

class GraphicsSettings;
class StateData;
class State;

class Game
{
public:
    Game();
    ~Game();

    void init_graphics_settings();
    void init_window();
    void init_supported_keys();
    void init_state_data();
    void init_states();

    void update_dt();
    void update_sfml_events();
    void update();
    void render();
    void run();
    void end_application();

private:
    std::stack<State *> m_states;
    std::map<std::string, int> m_supported_keys;
    std::shared_ptr<GraphicsSettings> m_gfx_settings;
    std::shared_ptr<StateData> m_state_data;
    std::string m_current_path;

    sf::RenderWindow * m_main_window;
    sf::Event m_sf_event;
    sf::Clock m_dt_clock;

    float m_dt;
};

#endif /* GAME_HPP */