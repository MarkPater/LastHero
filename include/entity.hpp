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

    void setTexture(sf::Texture & texture);
    void createMovementComponent(const float & maxVelocity, const float & acceleration, const float & deceleration);
    void createAnimationComponent(sf::Texture & texture_sheet);
    void createHitboxComponent(sf::Vector2f offset, sf::Vector2f size);

    virtual void setPosition(float x, float y);
    virtual void move(const float dir_x, const float dir_y);
    
    virtual void render(sf::RenderTarget * target);
    virtual void update(const float & dt);

protected:
    sf::Sprite m_sprite;

    HitboxComponent * m_hitboxComponent;
    MovementComponent * m_movementComponent;
    AnimationComponent * m_animationComponent;
};

#endif /* ENTITY_HPP */