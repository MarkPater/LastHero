#include "player.hpp"

Player::Player(float x, float y, sf::Texture & texture_sheet)
{
    setTexture(texture_sheet);
    setPosition(x, y);

    createMovementComponent(500.f, 20.f, 10.f);
    createAnimationComponent(texture_sheet);
    createHitboxComponent(sf::Vector2f(82, 63), sf::Vector2f(96, 112));

    m_animationComponent->addAnimation("IDLE_LEFT", 100.f, 0, 0, 13, 0, 192, 192);
    m_animationComponent->addAnimation("WALK_LEFT", 100.f, 0, 1, 11, 1, 192, 192);
}

Player::~Player()
{
}

void Player::update(const float & dt)
{
    m_movementComponent->update(dt);

    if (m_movementComponent->getState(MovementState::IDLE)) {
        m_animationComponent->play("IDLE_LEFT", dt);
    }
    else if (m_movementComponent->getState(MovementState::MOVING_LEFT)) {
        m_animationComponent->play("WALK_LEFT", dt);
    }
    
    m_hitboxComponent->update();
}