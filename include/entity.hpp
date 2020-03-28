#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "components/movementComponent.hpp"

class Entity 
{
public:
    Entity();
    ~Entity();

    void createMovementComponent(const float & maxVelocity, const float & acceleration, const float & deceleration);
    void setPosition(float x, float y);
    void setTexture(sf::Texture & texture);

    void move(const float dir_x, const float dir_y);
    void render(sf::RenderTarget * target);
    void update(const float & dt);

protected:
    sf::Sprite m_sprite;

    MovementComponent * m_movementComponent;
};

#endif /* ENTITY_HPP */