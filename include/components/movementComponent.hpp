#ifndef MOVEMENT_COMPONENT_HPP
#define MOVEMENT_COMPONENT_HPP

#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <vector>
#include <string> 
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

enum MovementState {
    IDLE = 0,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN
};

class MovementComponent
{
public:
    MovementComponent(sf::Sprite & sprite, float max_velocity, float acceleration, float deceleration);

    bool get_state(const unsigned short & state) const;
    sf::Vector2f get_velocity() const;
    float get_max_velocity() const; 
    
    void move(const float & dirX, const float & dirY);
    void update(const float & dt);

private:
    float m_max_velocity;
    float m_acceleration;
    float m_deceleration;

    sf::Sprite & m_sprite;
    sf::Vector2f m_velocity;
};

#endif /* MOVEMENT_COMPONENT_HPP */