#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity
{
public:
    Player(float x, float y, sf::Texture & texture_sheet);
    ~Player();

    virtual void update(float dt) override;

private:
    void update_attack();
    void update_annimation(float dt);

    bool m_attacking{ false };
};

#endif /* PLAYER_HPP */