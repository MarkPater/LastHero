#include "GUI/PauseMenu.hpp"

PauseMenu::PauseMenu(const sf::RenderWindow & window, sf::Font & font)
    : m_font(font)
{
    m_background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    m_background.setFillColor(sf::Color(20, 20, 20, 100));

    m_container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x/3.5), static_cast<float>(window.getSize().y/1.35)));
    m_container.setPosition(window.getSize().x / 2 - m_container.getSize().x / 2, (window.getSize().y - m_container.getSize().y) / 2);
    m_container.setFillColor(sf::Color(20, 20, 20, 200));

    m_menu_title.setFont(m_font);
    m_menu_title.setString("PAUSED");
    m_menu_title.setCharacterSize(50);
    m_menu_title.setColor(sf::Color(234, 25, 55, 200));
    m_menu_title.setPosition(m_container.getPosition().x + (m_container.getSize().x / 2) - (m_menu_title.getGlobalBounds().width / 2),
                            m_container.getPosition().y + 25);
}

PauseMenu::~PauseMenu()
{
    m_buttons.clear();
}

void PauseMenu::add_button(const std::string & action, sf::Text & text, float x, float y)
{
    std::string s_text = text.getString().toAnsiString();
    m_buttons[action] = std::unique_ptr<gui::Button>{ new gui::Button{ x, y, text.getGlobalBounds().width + 10, text.getGlobalBounds().height + 5, m_font, s_text } };

    m_buttons[action]->set_check_only_text(true);
    m_buttons[action]->set_button_colors();
}

bool PauseMenu::is_button_pressed(const std::string & action) const
{
    return m_buttons.at(action)->is_pressed();
}

const sf::RectangleShape & PauseMenu::get_container() const
{
    return m_container;
}

void PauseMenu::update(const sf::Vector2f & mousePos)
{   
    for (const auto & button : m_buttons) {
        button.second->update(mousePos);
    }
}

void PauseMenu::render(sf::RenderTarget & target)
{
    target.draw(m_background);
    target.draw(m_container);
    target.draw(m_menu_title);

    for (const auto & button : m_buttons) {
        button.second->render(target);
    }
}