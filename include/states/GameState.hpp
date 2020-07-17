#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "states/State.hpp"

#include <memory>

class Player;
class TileMap;
class StateData;
class PauseMenu;

class GameState : public State 
{
public:
    GameState(std::shared_ptr<StateData> state_data);
    ~GameState();

    virtual void init_keybinds() override;
    void init_textures();
    void init_players();
    void init_font();
    void init_pause_menu();
    void update_pause_menu_input();

    virtual void update_input() override;
    virtual void update_player_input();
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

protected:
    std::unique_ptr<Player> m_player;
    std::unique_ptr<PauseMenu> m_pause_menu;

    sf::Font m_font;
};

#endif /* GAME_STATE_HPP */