#include "components/movementComponent.hpp"

MovementComponent::MovementComponent(sf::Sprite & sprite, float maxVelocity, float acceleration, float deceleration) :
    m_sprite(sprite),
    m_maxVelocity(maxVelocity),
    m_acceleration(acceleration),
    m_deceleration(deceleration),
    m_velocity(sf::Vector2f(0, 0))
{
}

const bool MovementComponent::isIdle() const
{
    return (m_velocity.x == 0 && m_velocity.y == 0);
}

void MovementComponent::move(const float & dirX, const float & dirY)
{
    m_velocity.x += m_acceleration * dirX;
    m_velocity.y += m_acceleration * dirY;
}

void MovementComponent::update(const float & dt)
{
    // Horizontal deceleration
    if (m_velocity.x > 0) {
        if (m_velocity.x > m_maxVelocity) {
            m_velocity.x = m_maxVelocity;
        }
        if ((m_velocity.x -= m_deceleration) < 0) {
            m_velocity.x = 0;
        }
    }
    else if (m_velocity.x < 0) {
        if (m_velocity.x < -m_maxVelocity) {
            m_velocity.x = -m_maxVelocity;
        }
        if ((m_velocity.x += m_deceleration) > 0) {
            m_velocity.x = 0;
        }
    }

    // Vertical deceleration
    if (m_velocity.y > 0) {
        if (m_velocity.y > m_maxVelocity) {
            m_velocity.y = m_maxVelocity;
        }
        if ((m_velocity.y -= m_deceleration) < 0) {
            m_velocity.y = 0;
        }
    }
    else if (m_velocity.y < 0) {
        if (m_velocity.y < -m_maxVelocity) {
            m_velocity.y = -m_maxVelocity;
        }
        if ((m_velocity.y += m_deceleration) > 0) {
            m_velocity.y = 0;
        }
    }

    m_sprite.move(m_velocity * dt);
}