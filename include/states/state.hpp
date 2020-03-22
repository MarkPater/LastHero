#ifndef STATE_HPP
#define STATE_HPP

#include "entity.hpp"
class State {
public:
    State(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys);
    virtual ~State();

    virtual void initKeybinds() = 0;

    void checkForQuit();
    const bool & getQuit() const;

    virtual void updateKeybinds(const float & dt) = 0;
    virtual void update(const float & dt) = 0;
    virtual void render(sf::RenderTarget * target = nullptr) = 0;
    virtual void endState() = 0;

protected:
    std::vector<sf::Texture *> m_textures;
    std::map<std::string, int> * m_supportedKeys;
    std::map<std::string, int> m_keybinds;

    sf::RenderWindow * m_window;

    bool m_quit;
};

#endif /* STATE_HPP */