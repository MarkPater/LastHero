#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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

private:
    std::vector<sf::Texture *> m_textures;
    sf::RenderWindow * m_window;
    bool m_quit;
};

#endif /* STATE_HPP */