#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "components/movementComponent.hpp"
#include "components/animationComponent.hpp"
#include "components/hitboxComponent.hpp"

class Entity 
{
public:
    Entity();
    ~Entity();

    void set_texture(sf::Texture & texture);
    void create_movement_component(const float & max_velocity, const float & acceleration, const float & deceleration);
    void create_animation_component(sf::Texture & texture_sheet);
    void create_hitbox_component(sf::Vector2f offset, sf::Vector2f size);

    virtual void set_position(float x, float y);
    virtual void move(const float dir_x, const float dir_y);
    virtual void render(sf::RenderTarget * target);
    virtual void update(const float & dt) = 0;

protected:
    sf::Sprite m_sprite;

    HitboxComponent * m_hitbox_component;
    MovementComponent * m_movement_component;
    AnimationComponent * m_animation_component;
};

#endif /* ENTITY_HPP */