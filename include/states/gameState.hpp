#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "states/state.hpp"
#include "GUI/pauseMenu.hpp"

class GameState : public State 
{
public:
    GameState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states);
    ~GameState();

    virtual void initKeybinds() override;
    void initTextures();
    void initPlayers();
    void initFont();
    void initPauseMenu();
    void updatePauseMenuButtons();

    virtual void updateInput() override;
    virtual void updatePlayerInput();
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

protected:
    sf::Font m_font;

    Player * m_player;
    PauseMenu * m_pauseMenu;
};

#endif /* GAME_STATE_HPP */