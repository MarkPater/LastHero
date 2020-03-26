#include <entity.hpp>

Entity::Entity() :
    m_sprite(nullptr),
    m_texture(nullptr),
    m_movementSpeed(300.f)
{
}

Entity::~Entity()
{
    delete m_sprite;
}

void Entity::createSprite(sf::Texture * texture)
{
    m_texture = texture;
}

void Entity::move(const float & dt, const float dir_x, const float dir_y)
{
    if (m_sprite) {
        m_sprite->move(m_movementSpeed * dir_x * dt, m_movementSpeed * dir_y * dt);
    }
}

void Entity::update(const float & dt)
{
}

void Entity::render(sf::RenderTarget * target)
{
    if (m_sprite) {
        target->draw(*m_sprite);
    }
}