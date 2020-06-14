#ifndef GAME_HPP
#define GAME_HPP

#include "states/MainMenuState.hpp"
#include <memory>

class GraphicsSettings;

class Game
{
public:
    Game();
    ~Game();

    void init_graphics_settings();
    void init_window();
    void init_supported_keys();
    void init_states();
    void update_dt();
    void update_sfml_events();
    void update();
    void render();
    void run();
    void end_application();

private:
    std::shared_ptr<GraphicsSettings> m_gfx_settings;
    sf::RenderWindow * m_main_window;
    sf::Event m_sf_event;
    sf::Clock m_dt_clock;

    std::stack<State *> m_states;
    std::map<std::string, int> m_supported_keys;

    float m_dt;
    std::string m_current_path;
};

#endif /* GAME_HPP */