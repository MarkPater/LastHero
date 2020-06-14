#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "states/state.hpp"
#include "GUI/pauseMenu.hpp"

class GameState : public State 
{
public:
    GameState(sf::RenderWindow * window, std::map<std::string, int> * supported_keys, std::stack<State *> * states);
    ~GameState();

    virtual void init_keybinds() override;
    void init_textures();
    void init_players();
    void init_font();
    void init_pause_menu();
    void update_pause_menu_buttons();

    virtual void update_input() override;
    virtual void update_player_input();
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

protected:
    sf::Font m_font;

    Player * m_player;
    PauseMenu * m_pause_menu;
};

#endif /* GAME_STATE_HPP */