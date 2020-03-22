#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
class Entity 
{
public:
    Entity();
    ~Entity();

    void move(const float & dt, const float dir_x, const float dir_y);
    void render(sf::RenderTarget * target);
    void update(const float & dt);

protected:
    sf::RectangleShape m_testRect;
    float m_movementSpeed;
};

#endif