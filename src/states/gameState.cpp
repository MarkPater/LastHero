#include "states/gameState.hpp"

GameState::GameState(sf::RenderWindow * window) :
    State(window)
{
    std::cout << "Create GameState()";
}

GameState::~GameState()
{
}

void GameState::updateKeybinds(const float & dt) 
{
    checkForQuit();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        std::cout << "A\n";
    }
}

void GameState::update(const float & dt)
{
    updateKeybinds(dt);
}

void GameState::render(sf::RenderTarget * target)
{
}

void GameState::endState()
{
    std::cout << "The end of GameState\n";
}