#include <entity.hpp>

Entity::Entity() :
    m_movementComponent(nullptr),
    m_animationComponent(nullptr)
{
}

Entity::~Entity()
{
    delete m_movementComponent;
    delete m_animationComponent;
}

void Entity::setTexture(sf::Texture & texture)
{
    m_sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float & maxVelocity, const float & acceleration, const float & deceleration)
{
    m_movementComponent = new MovementComponent(m_sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture & texture_sheet)
{
    m_animationComponent = new AnimationComponent(m_sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Vector2f offset, sf::Vector2f size)
{
    m_hitboxComponent = new HitboxComponent(m_sprite, offset, size);
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
}

void Entity::render(sf::RenderTarget * target)
{
    target->draw(m_sprite);

    m_hitboxComponent->render(*target);
}