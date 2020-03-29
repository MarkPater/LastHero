#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Button
{
public:
    Button(const float & x, const float & y, 
           const float & width, const float & height,
           sf::Font * font, std::string text, unsigned characterSize,
           sf::Color idleTextColor, sf::Color hoverTextColor, sf::Color activeTextColor,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();

    enum class buttonState {
        BTN_IDLE = 0,
        BTN_HOVER,
        BTN_ACTIVE
    };

    const bool isPressed() const;
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget & target);

private:
    sf::RectangleShape m_buttonShape;
    sf::Font * m_font;
    sf::Text m_text;

    sf::Color m_idleColor;
    sf::Color m_hoverColor;
    sf::Color m_activeColor;
    sf::Color m_idleTextColor;
    sf::Color m_hoverTextColor;
    sf::Color m_activeTextColor;

    unsigned short m_buttonState;
};

#endif /* BUTTON_HPP */