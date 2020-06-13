#include "GUI/pauseMenu.hpp"

PauseMenu::PauseMenu(const sf::RenderWindow & window, sf::Font & font)
    : m_font(font)
{
    m_background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    m_background.setFillColor(sf::Color(20, 20, 20, 100));

    m_container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x/3.5), static_cast<float>(window.getSize().y/1.35)));
    m_container.setPosition(window.getSize().x / 2 - m_container.getSize().x / 2, (window.getSize().y - m_container.getSize().y) / 2);
    m_container.setFillColor(sf::Color(20, 20, 20, 200));

    m_menuTitle.setFont(m_font);
    m_menuTitle.setString("PAUSED");
    m_menuTitle.setCharacterSize(50);
    m_menuTitle.setColor(sf::Color(234, 25, 55, 200));
    m_menuTitle.setPosition(m_container.getPosition().x + (m_container.getSize().x / 2) - (m_menuTitle.getGlobalBounds().width / 2),
                            m_container.getPosition().y + 25);
}

PauseMenu::~PauseMenu()
{
    for (auto & button : m_buttons) {
        delete button.second;
    }
    m_buttons.clear();
}

void PauseMenu::addButton(const std::string & action, sf::Text & text, const float & x, const float & y)
{
    std::string s_text = text.getString().toAnsiString();
    m_buttons[action] = new gui::Button(x, y, text.getGlobalBounds().width + 10, text.getGlobalBounds().height + 5, m_font, s_text);

    m_buttons[action]->set_check_only_text(true);
    m_buttons[action]->set_button_colors();
}

bool PauseMenu::isButtonPressed(const std::string & action) const
{
    return m_buttons.at(action)->is_pressed();
}

const sf::RectangleShape & PauseMenu::getContainer()
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
    target.draw(m_menuTitle);

    for (const auto & button : m_buttons) {
        button.second->render(target);
    }
}