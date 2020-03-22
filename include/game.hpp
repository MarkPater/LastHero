#ifndef GAME_HPP
#define GAME_HPP

#include "states/gameState.hpp"

class Game
{
public:
    Game();
    ~Game();

    void initWindow();
    void initStates();
    void updateDt();
    void updateSfmlEvents();
    void update();
    void render();
    void run();
    void endApplication();

private:
    sf::RenderWindow * m_mainWindow;
    sf::Event m_sfEvent;
    sf::Clock m_dtClock;

    std::stack<State *> m_states;

    float m_dt;
};

#endif /* GAME_HPP */