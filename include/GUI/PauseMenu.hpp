#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include "GUI/Gui.hpp"

#include <map>
#include <memory>

class PauseMenu
{
public:
    PauseMenu(const sf::RenderWindow & window, sf::Font & font);
    virtual ~PauseMenu();

    void add_button(const std::string & action, sf::Text & text, float x, float y);
    bool is_button_pressed(const std::string & action) const;
    void update(const sf::Vector2f & mousePos);
    void render(sf::RenderTarget & target);
    const sf::RectangleShape & get_container() const;

private:
    std::map<std::string, std::unique_ptr<gui::Button>> m_buttons;

    sf::RectangleShape m_background;
    sf::RectangleShape m_container;
    sf::Text m_menu_title;
    sf::Font & m_font;
};

#endif /* PAUSE_MENU_HPP */