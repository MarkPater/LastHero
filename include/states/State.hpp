#ifndef STATE_HPP
#define STATE_HPP

#include "Player.hpp"
#include <memory>

class GraphicsSettings;
class StateData;

class State
{
public:
    State(std::shared_ptr<StateData> state_data);
    virtual ~State();

    const bool & get_quit() const;
    void pause_menu();
    void unpause_menu();
    virtual void end_state();
    virtual void update_mouse_pos();
    virtual void init_mouse_pos_text();
    virtual void update_mouse_pos_text();
    virtual void init_keybinds() = 0;
    virtual void update_input() = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderTarget * target = nullptr) = 0;

protected:
    void update_exit_delay_time(float dt);
    bool exit_delay_occurred();

    std::shared_ptr<StateData> m_state_data;
    std::shared_ptr<GraphicsSettings> m_gfx_settings;
    std::map<std::string, int> * m_supported_keys;
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, int> m_keybinds;
    std::stack<State *> * m_states;
    std::string m_current_path;

    sf::RenderWindow * m_window;
    sf::Vector2i m_mouse_pos_screen;
    sf::Vector2i m_mouse_pos_window;
    sf::Vector2f m_mouse_pos_view;
    sf::Vector2i m_mouse_pos_grid;
    sf::Text m_mouse_pos_text;

    bool m_quit;
    bool m_paused;
    float m_exit_delay_time;
    const float m_max_exit_delay_time;
};

#endif /* STATE_HPP */