#include "components/HitboxComponent.hpp"

HitboxComponent::HitboxComponent(sf::Sprite & sprite, sf::Vector2f offset, sf::Vector2f size)
    : m_sprite(sprite)
    , m_offset(offset)
{
    m_hitbox.setPosition(sprite.getGlobalBounds().left + offset.x, sprite.getGlobalBounds().top + offset.y);
    m_hitbox.setSize(size);
    m_hitbox.setFillColor(sf::Color::Transparent);
    m_hitbox.setOutlineThickness(1.f);
    m_hitbox.setOutlineColor(sf::Color::Green);
}

bool HitboxComponent::check_intersect(const sf::FloatRect & frect)
{
    return m_hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
    m_hitbox.setPosition(m_sprite.getPosition().x + m_offset.x, m_sprite.getPosition().y + m_offset.y);
}

void HitboxComponent::render(sf::RenderTarget & target)
{
    target.draw(m_hitbox);
}