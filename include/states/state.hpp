#ifndef STATE_HPP
#define STATE_HPP

#include "entity.hpp"
class State 
{
public:
    State(sf::RenderWindow * window);
    virtual ~State();

    void checkForQuit();
    const bool & getQuit() const;

    virtual void updateKeybinds(const float & dt) = 0;
    virtual void update(const float & dt) = 0;
    virtual void render(sf::RenderTarget * target = nullptr) = 0;
    virtual void endState() = 0;

protected:
    std::vector<sf::Texture *> m_textures;
    sf::RenderWindow * m_window;
    bool m_quit;
};

#endif /* STATE_HPP */