#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "components/MovementComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/HitboxComponent.hpp"

class Entity 
{
public:
    Entity();
    ~Entity();

    void set_texture(sf::Texture & texture);
    void create_movement_component(float max_velocity, float acceleration, float deceleration);
    void create_animation_component(sf::Texture & texture_sheet);
    void create_hitbox_component(sf::Vector2f offset, sf::Vector2f size);

    virtual void set_position(float x, float y);
    virtual void move(float dir_x, float dir_y);
    virtual void render(sf::RenderTarget * target);
    virtual void update(float dt) = 0;

protected:
    sf::Sprite m_sprite;

    HitboxComponent * m_hitbox_component;
    MovementComponent * m_movement_component;
    AnimationComponent * m_animation_component;
};

#endif /* ENTITY_HPP */