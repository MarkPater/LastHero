#ifndef HITBOX_COMPONENT_HPP
#define HITBOX_COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class HitboxComponent
{
public:
    HitboxComponent(sf::Sprite & sprite, sf::Vector2f offset, sf::Vector2f size);

    bool checkIntersect(const sf::FloatRect & frect);
    void update();
    void render(sf::RenderTarget & target);

private:
    sf::RectangleShape m_hitbox;
    sf::Sprite & m_sprite;
    sf::Vector2f m_offset;
};

#endif /* HITBOX_COMPONENT_HPP */