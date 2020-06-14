#ifndef GAME_HPP
#define GAME_HPP

#include "states/MainMenuState.hpp"

class Game
{
public:
    Game();
    ~Game();

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
    sf::RenderWindow * m_main_window;
    sf::Event m_sf_event;
    sf::Clock m_dt_clock;
    sf::VideoMode m_window_bounds;

    std::stack<State *> m_states;
    std::map<std::string, int> m_supported_keys;
    std::vector<sf::VideoMode> m_video_modes;

    float m_dt;
    bool m_is_fullscreen;
    int m_framerate_limit;
    std::string m_window_title;
    std::string m_current_path;
};

#endif /* GAME_HPP */