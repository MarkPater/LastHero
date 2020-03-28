#include <entity.hpp>

Entity::Entity() :
    m_movementComponent(nullptr)
{
}

Entity::~Entity()
{
    delete m_movementComponent;
}

void Entity::setTexture(sf::Texture & texture)
{
    m_sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float & maxVelocity, const float & acceleration, const float & deceleration)
{
    m_movementComponent = new MovementComponent(m_sprite, maxVelocity, acceleration, deceleration);
}

void Entity::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y)
{
    if (m_movementComponent) {
        m_movementComponent->move(dir_x, dir_y);
    }
}

void Entity::update(const float & dt)
{
    if (m_movementComponent) {
        m_movementComponent->update(dt);
    }
}

void Entity::render(sf::RenderTarget * target)
{
    target->draw(m_sprite);
}