#include "button.hpp"

Button::Button(const float & x, const float & y, 
               const float & width, const float & height,
               sf::Font * font, std::string text, unsigned characterSize,
               sf::Color idleTextColor, sf::Color hoverTextColor, sf::Color activeTextColor,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) :
    m_buttonState(static_cast<unsigned short>(buttonState::BTN_IDLE))
{
    m_buttonShape.setPosition(x, y);
    m_buttonShape.setSize(sf::Vector2f(width, height));
    m_buttonShape.setFillColor(idleColor);

    m_font = font;
    m_text.setFont(*font);
    m_text.setString(text);
    m_text.setCharacterSize(characterSize);
    m_text.setStyle(sf::Text::Style::Italic);
    m_text.setPosition(
        m_buttonShape.getPosition().x + width / 2 - m_text.getGlobalBounds().width / 2,
        m_buttonShape.getPosition().y + height / 2 - m_text.getGlobalBounds().height / 1.25f
    );

    m_idleColor = idleColor;
    m_hoverColor = hoverColor;
    m_activeColor = activeColor;
    m_idleTextColor = idleTextColor;
    m_hoverTextColor = hoverTextColor;
    m_activeTextColor = activeTextColor;
}

Button::~Button()
{

}

const bool Button::isPressed() const
{
    return m_buttonState == static_cast<unsigned short>(buttonState::BTN_ACTIVE) ? true : false;
}

void Button::update(sf::Vector2f mousePos)
{
    m_buttonState = static_cast<unsigned short>(buttonState::BTN_IDLE);

    if (m_text.getGlobalBounds().contains(mousePos)) {
        m_buttonState = static_cast<unsigned short>(buttonState::BTN_HOVER);
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            m_buttonState = static_cast<unsigned short>(buttonState::BTN_ACTIVE);
        }
    }

    switch (m_buttonState) {
        case static_cast<unsigned short>(buttonState::BTN_IDLE): {   
            m_buttonShape.setFillColor(m_idleColor);
            m_text.setFillColor(m_idleTextColor);
            m_text.setOutlineThickness(2.5);
            break;
        }
        case static_cast<unsigned short>(buttonState::BTN_HOVER): {   
            m_buttonShape.setFillColor(m_hoverColor);
            m_text.setFillColor(m_hoverTextColor);
            m_text.setOutlineThickness(5);
            break;
        }
        case static_cast<unsigned short>(buttonState::BTN_ACTIVE): {   
            m_buttonShape.setFillColor(m_activeColor);
            m_text.setFillColor(m_activeTextColor);
            break;
        }
        default: {
            m_buttonShape.setFillColor(sf::Color::Red);
            m_text.setFillColor(sf::Color::Red);
            break;
        }
    }
}

void Button::render(sf::RenderTarget & target)
{
    target.draw(m_buttonShape);
    target.draw(m_text);
}