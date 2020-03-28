#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "components/movementComponent.hpp"
#include "components/animationComponent.hpp"

class Entity 
{
public:
    Entity();
    ~Entity();

    void setTexture(sf::Texture & texture);
    void createMovementComponent(const float & maxVelocity, const float & acceleration, const float & deceleration);
    void createAnimationComponent(sf::Texture & texture_sheet);
    
    virtual void setPosition(float x, float y);
    virtual void move(const float dir_x, const float dir_y);
    
    virtual void render(sf::RenderTarget * target);
    virtual void update(const float & dt);

protected:
    sf::Sprite m_sprite;

    MovementComponent * m_movementComponent;
    AnimationComponent * m_animationComponent;
};

#endif /* ENTITY_HPP */