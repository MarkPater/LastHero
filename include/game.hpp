#ifndef GAME_HPP
#define GAME_HPP

#include "states/mainMenuState.hpp"

class Game
{
public:
    Game();
    ~Game();

    void initWindow();
    void initSupportedKeys();
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
    sf::VideoMode m_windowBounds;

    std::stack<State *> m_states;
    std::map<std::string, int> m_supportedKeys;
    std::vector<sf::VideoMode> m_videoModes;

    float m_dt;
    bool m_isFullscreen;
    int m_framerateLimit;
    std::string m_windowTitle;
    std::string m_currentPath;
};

#endif /* GAME_HPP */