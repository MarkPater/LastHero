#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"

class Player : public Entity
{
public:
    Player(float x, float y, sf::Texture & texture_sheet);
    ~Player();

    virtual void update(const float & dt) override;
};

#endif /* PLAYER_HPP */