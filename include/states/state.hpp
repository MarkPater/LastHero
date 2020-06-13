#ifndef STATE_HPP
#define STATE_HPP

#include "player.hpp"
class State
{
public:
    State(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states);
    virtual ~State();

    const bool & getQuit() const;
    void pauseMenu();
    void unpauseMenu();
    void updateDelayTime(float dt);
    bool delayOccurred();
    virtual void endState();
    virtual void updateMousePos();
    virtual void initKeybinds() = 0;
    virtual void updateInput() = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderTarget * target = nullptr) = 0;

protected:
    std::stack<State *> * m_states;
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, int> * m_supportedKeys;
    std::map<std::string, int> m_keybinds;

    sf::RenderWindow * m_window;
    sf::Vector2i m_mousePosScreen;
    sf::Vector2i m_mousePosWindow;
    sf::Vector2f m_mousePosView;

    bool m_quit;
    bool m_paused;
    float m_delayTime;
    const float m_maxDelayTime;
    std::string m_currentPath;
};

#endif /* STATE_HPP */