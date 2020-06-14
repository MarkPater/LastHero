#include <entity.hpp>

Entity::Entity()
    : m_movement_component(nullptr)
    , m_animation_component(nullptr)
    , m_hitbox_component(nullptr)
{
}

Entity::~Entity()
{
    delete m_movement_component;
    delete m_animation_component;
    delete m_hitbox_component;
}

void Entity::set_texture(sf::Texture & texture)
{
    m_sprite.setTexture(texture);
}

void Entity::create_movement_component(const float & maxVelocity, const float & acceleration, const float & deceleration)
{
    m_movement_component = new MovementComponent(m_sprite, maxVelocity, acceleration, deceleration);
}

void Entity::create_animation_component(sf::Texture & texture_sheet)
{
    m_animation_component = new AnimationComponent(m_sprite, texture_sheet);
}

void Entity::create_hitbox_component(sf::Vector2f offset, sf::Vector2f size)
{
    m_hitbox_component = new HitboxComponent(m_sprite, offset, size);
}

void Entity::set_position(float x, float y)
{
    m_sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y)
{
    if (m_movement_component) {
        m_movement_component->move(dir_x, dir_y);
    }
}

void Entity::render(sf::RenderTarget * target)
{
    target->draw(m_sprite);

    m_hitbox_component->render(*target);
}