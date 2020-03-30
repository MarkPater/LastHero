#include "player.hpp"

Player::Player(float x, float y, sf::Texture & texture_sheet)
{
    setTexture(texture_sheet);
    setPosition(x, y);

    createMovementComponent(600.f, 15.4f, 10.f);
    createAnimationComponent(texture_sheet);
    createHitboxComponent(sf::Vector2f(86, 66), sf::Vector2f(86, 111));

    m_animationComponent->addAnimation("IDLE", 9.f, 0, 0, 13, 0, 192, 192);
    m_animationComponent->addAnimation("WALK", 8.5f, 0, 1, 11, 1, 192, 192);
    m_animationComponent->addAnimation("ATTACK", 7.f, 0, 2, 13, 2, 192*2, 192);
}

Player::~Player()
{
}

void Player::update(const float & dt)
{
    m_movementComponent->update(dt);

    if (m_movementComponent->getState(MovementState::IDLE)) {
        m_animationComponent->play("IDLE", dt, m_movementComponent->getMaxVelocity(), m_movementComponent->getMaxVelocity());
    }
    else if (m_movementComponent->getState(MovementState::MOVING_LEFT)) {
        m_sprite.setOrigin(0.f, 0.f);
        m_sprite.setScale(1.f, 1.f);
        m_animationComponent->play("WALK", dt, m_movementComponent->getVelocity().x, m_movementComponent->getMaxVelocity());
    }
    else if (m_movementComponent->getState(MovementState::MOVING_RIGHT)) {
        m_sprite.setOrigin(258.f, 0.f);
        m_sprite.setScale(-1.f, 1.f);
        m_animationComponent->play("WALK", dt, m_movementComponent->getVelocity().x, m_movementComponent->getMaxVelocity());
    }
    else if (m_movementComponent->getState(MovementState::MOVING_UP)) {
        m_animationComponent->play("WALK", dt, m_movementComponent->getVelocity().y, m_movementComponent->getMaxVelocity());
    }
    else if (m_movementComponent->getState(MovementState::MOVING_DOWN)) {
        m_animationComponent->play("WALK", dt, m_movementComponent->getVelocity().y, m_movementComponent->getMaxVelocity());
    }
    
    m_hitboxComponent->update();
}