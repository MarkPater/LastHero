#include <entity.hpp>

Entity::Entity() :
    m_movementSpeed(300.f),
    m_testRect(sf::Vector2f(100.f, 100.f))
{
    m_testRect.setFillColor(sf::Color::White);
}

Entity::~Entity()
{

}

void Entity::move(const float & dt, const float dir_x, const float dir_y)
{
    m_testRect.move(m_movementSpeed * dir_x * dt, m_movementSpeed * dir_y * dt);
}

void Entity::update(const float & dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        move(dt, -1.0f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        move(dt, 1.0f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        move(dt, 0.f, -1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        move(dt, 0.f, 1.f);
    }
}

void Entity::render(sf::RenderTarget * target)
{
    target->draw(m_testRect);
}