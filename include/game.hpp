#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Game
{
public:
    Game();
    ~Game();

    void init();
    void updateDt();
    void update();
    void render();
    void run();

private:
    sf::RenderWindow * m_mainWindow;
    sf::Event m_sfEvent;
    sf::Clock dtClock;
    float dt;
};

#endif /* GAME_H */