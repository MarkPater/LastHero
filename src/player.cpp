#include "player.hpp"

const size_t heroWidth{ 192 };

Player::Player(float x, float y, sf::Texture & texture_sheet)
{
    setTexture(texture_sheet);
    setPosition(x, y);

    createMovementComponent(600.f, 15.0f, 10.f);
    createAnimationComponent(texture_sheet);
    createHitboxComponent(sf::Vector2f(86, 66), sf::Vector2f(86, 111));

    m_animationComponent->addAnimation("IDLE", 9.f, 0, 0, 13, 0, heroWidth, heroWidth);
    m_animationComponent->addAnimation("WALK", 8.5f, 0, 1, 11, 1, heroWidth, heroWidth);
    m_animationComponent->addAnimation("ATTACK", 5.5f, 0, 2, 13, 2, heroWidth*2, heroWidth);
}

Player::~Player()
{
}

void Player::update(const float & dt)
{
    m_movementComponent->update(dt);
    updateAttack();
    updateAnnimation(dt);
    m_hitboxComponent->update();
}

void Player::updateAttack()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        m_attacking = true;
    }
}

void Player::updateAnnimation(const float & dt)
{
    if (m_attacking) {
        if (m_sprite.getScale().x > 0) {        // left
            m_sprite.setOrigin(heroWidth/2, 0);
        }
        else if (m_sprite.getScale().x < 0) {   // right
            m_sprite.setOrigin(258 + heroWidth/2, 0);
        }

        if (m_animationComponent->play("ATTACK", dt, m_movementComponent->getMaxVelocity(), m_movementComponent->getMaxVelocity(), m_attacking)) {
            m_attacking = false;

            if (m_sprite.getScale().x > 0) {
                m_sprite.setOrigin(0, 0);
            }
            else if (m_sprite.getScale().x < 0) {
                m_sprite.setOrigin(258, 0);
            }
        }
    }
    else if (m_movementComponent->getState(MovementState::IDLE)) {
        m_animationComponent->play("IDLE", dt, m_movementComponent->getMaxVelocity(), m_movementComponent->getMaxVelocity());
    }
    else if (m_movementComponent->getState(MovementState::MOVING_LEFT)) {
        if (m_sprite.getScale().x < 0) {
            m_sprite.setOrigin(0.f, 0.f);
            m_sprite.setScale(1.f, 1.f);
        }
        m_animationComponent->play("WALK", dt, m_movementComponent->getVelocity().x, m_movementComponent->getMaxVelocity());
    }
    else if (m_movementComponent->getState(MovementState::MOVING_RIGHT)) {
        if (m_sprite.getScale().x > 0) {
            m_sprite.setOrigin(258.f, 0.f);
            m_sprite.setScale(-1.f, 1.f);
        }
        m_animationComponent->play("WALK", dt, m_movementComponent->getVelocity().x, m_movementComponent->getMaxVelocity());
    }
    else if (m_movementComponent->getState(MovementState::MOVING_UP)) {
        m_animationComponent->play("WALK", dt, m_movementComponent->getVelocity().y, m_movementComponent->getMaxVelocity());
    }
    else if (m_movementComponent->getState(MovementState::MOVING_DOWN)) {
        m_animationComponent->play("WALK", dt, m_movementComponent->getVelocity().y, m_movementComponent->getMaxVelocity());
    }
}