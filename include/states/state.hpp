#ifndef STATE_HPP
#define STATE_HPP

#include "entity.hpp"
class State {
public:
    State(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states);
    virtual ~State();

    virtual void initKeybinds() = 0;

    const bool & getQuit() const;
    virtual void endState();

    virtual void updateMousePos();
    virtual void updateKeybinds(const float & dt) = 0;
    virtual void update(const float & dt) = 0;
    virtual void render(sf::RenderTarget * target = nullptr) = 0;

protected:
    std::stack<State *> * m_states;
    std::vector<sf::Texture *> m_textures;
    std::map<std::string, int> * m_supportedKeys;
    std::map<std::string, int> m_keybinds;

    sf::RenderWindow * m_window;
    sf::Vector2i m_mousePosScreen;
    sf::Vector2i m_mousePosWindow;
    sf::Vector2f m_mousePosView;

    bool m_quit;
};

#endif /* STATE_HPP */