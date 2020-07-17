#include "Player.hpp"

const size_t HERO_WIDTH{ 192 };

Player::Player(float x, float y, sf::Texture & texture_sheet)
{
    set_texture(texture_sheet);
    set_position(x, y);

    create_movement_component(600.f, 15.0f, 10.f);
    create_animation_component(texture_sheet);
    create_hitbox_component(sf::Vector2f(86, 66), sf::Vector2f(86, 111));

    m_animation_component->add_animation("IDLE", 9.f, 0, 0, 13, 0, HERO_WIDTH, HERO_WIDTH);
    m_animation_component->add_animation("WALK", 8.5f, 0, 1, 11, 1, HERO_WIDTH, HERO_WIDTH);
    m_animation_component->add_animation("ATTACK", 5.5f, 0, 2, 13, 2, HERO_WIDTH*2, HERO_WIDTH);
}

Player::~Player()
{
}

void Player::update(float dt)
{
    m_movement_component->update(dt);
    update_attack();
    update_annimation(dt);
    m_hitbox_component->update();
}

void Player::update_attack()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        m_attacking = true;
    }
}

void Player::update_annimation(float dt)
{
    if (m_attacking) {
        if (m_sprite.getScale().x > 0) {        // left
            m_sprite.setOrigin(HERO_WIDTH/2, 0);
        }
        else if (m_sprite.getScale().x < 0) {   // right
            m_sprite.setOrigin(258 + HERO_WIDTH/2, 0);
        }

        if (m_animation_component->play("ATTACK", dt, m_movement_component->get_max_velocity(), m_movement_component->get_max_velocity(), m_attacking)) {
            m_attacking = false;

            if (m_sprite.getScale().x > 0) {
                m_sprite.setOrigin(0, 0);
            }
            else if (m_sprite.getScale().x < 0) {
                m_sprite.setOrigin(258, 0);
            }
        }
    }
    else if (m_movement_component->get_state(MovementState::IDLE)) {
        m_animation_component->play("IDLE", dt, m_movement_component->get_max_velocity(), m_movement_component->get_max_velocity());
    }
    else if (m_movement_component->get_state(MovementState::MOVING_LEFT)) {
        if (m_sprite.getScale().x < 0) {
            m_sprite.setOrigin(0.f, 0.f);
            m_sprite.setScale(1.f, 1.f);
        }
        m_animation_component->play("WALK", dt, m_movement_component->get_velocity().x, m_movement_component->get_max_velocity());
    }
    else if (m_movement_component->get_state(MovementState::MOVING_RIGHT)) {
        if (m_sprite.getScale().x > 0) {
            m_sprite.setOrigin(258.f, 0.f);
            m_sprite.setScale(-1.f, 1.f);
        }
        m_animation_component->play("WALK", dt, m_movement_component->get_velocity().x, m_movement_component->get_max_velocity());
    }
    else if (m_movement_component->get_state(MovementState::MOVING_UP)) {
        m_animation_component->play("WALK", dt, m_movement_component->get_velocity().y, m_movement_component->get_max_velocity());
    }
    else if (m_movement_component->get_state(MovementState::MOVING_DOWN)) {
        m_animation_component->play("WALK", dt, m_movement_component->get_velocity().y, m_movement_component->get_max_velocity());
    }
}