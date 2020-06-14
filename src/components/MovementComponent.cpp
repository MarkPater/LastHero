#include "components/MovementComponent.hpp"

MovementComponent::MovementComponent(sf::Sprite & sprite, float maxVelocity, float acceleration, float deceleration)
    : m_sprite(sprite)
    , m_max_velocity(maxVelocity)
    , m_acceleration(acceleration)
    , m_deceleration(deceleration)
    , m_velocity(sf::Vector2f(0, 0))
{
}

bool MovementComponent::get_state(const unsigned short & state) const
{
    switch (state) {
        case MovementState::IDLE: {
            return (m_velocity.x == 0 && m_velocity.y == 0);
        }
        case MovementState::MOVING_LEFT: {
            return m_velocity.x < 0;
        }
        case MovementState::MOVING_RIGHT: {
            return m_velocity.x > 0;
        }
        case MovementState::MOVING_UP: {
            return m_velocity.y < 0;
        }
        case MovementState::MOVING_DOWN: {
            return m_velocity.y > 0;
        }
        default: {
            return false;
        }
    }
}

sf::Vector2f MovementComponent::get_velocity() const
{
    return m_velocity;
}

float MovementComponent::get_max_velocity() const
{
    return m_max_velocity;
}

void MovementComponent::move(const float & dirX, const float & dirY)
{
    m_velocity.x += m_acceleration * dirX;
    m_velocity.y += m_acceleration * dirY;
}

void MovementComponent::update(const float & dt)
{
    // Horizontal move
    if (m_velocity.x > 0) {
        if (m_velocity.x > m_max_velocity) {
            m_velocity.x = m_max_velocity;
        }
        if ((m_velocity.x -= m_deceleration) < 0) {
            m_velocity.x = 0;
        }
    }
    else if (m_velocity.x < 0) {
        if (m_velocity.x < -m_max_velocity) {
            m_velocity.x = -m_max_velocity;
        }
        if ((m_velocity.x += m_deceleration) > 0) {
            m_velocity.x = 0;
        }
    }

    // Vertical move
    if (m_velocity.y > 0) {
        if (m_velocity.y > m_max_velocity) {
            m_velocity.y = m_max_velocity;
        }
        if ((m_velocity.y -= m_deceleration) < 0) {
            m_velocity.y = 0;
        }
    }
    else if (m_velocity.y < 0) {
        if (m_velocity.y < -m_max_velocity) {
            m_velocity.y = -m_max_velocity;
        }
        if ((m_velocity.y += m_deceleration) > 0) {
            m_velocity.y = 0;
        }
    }

    m_sprite.move(m_velocity * dt);
}