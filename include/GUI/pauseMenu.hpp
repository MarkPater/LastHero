#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include "GUI/gui.hpp"
#include "string"

class PauseMenu
{
public:
    PauseMenu(const sf::RenderWindow & window, sf::Font & font);
    virtual ~PauseMenu();

    void addButton(const std::string & action, sf::Text & text, const float & x, const float & y);
    bool isButtonPressed(const std::string & action) const;
    void update(const sf::Vector2f & mousePos);
    void render(sf::RenderTarget & target);
    const sf::RectangleShape & getContainer();

private:
    sf::RectangleShape m_background;
    sf::RectangleShape m_container;
    sf::Text m_menuTitle;
    sf::Font & m_font;

    std::map<std::string, gui::Button *> m_buttons;
};

#endif /* PAUSE_MENU_HPP */