#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"

class Player : public Entity
{
public:
    Player(float x, float y, sf::Texture & texture);
    ~Player();
    
private:
    void initComponents();
};

#endif /* PLAYER_HPP */