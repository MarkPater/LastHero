#include "player.hpp"

Player::Player(float x, float y, sf::Texture & texture)
{
    setTexture(texture);
    setPosition(x, y);
    initComponents();
}

void Player::initComponents()
{
    createMovementComponent(500.f, 30.f, 10.f);
}

Player::~Player()
{
}