#include "states/gameState.hpp"

GameState::GameState(sf::RenderWindow * window) :
    State(window)
{
    std::cout << "Create GameState()\n";
}

GameState::~GameState()
{
}

void GameState::updateKeybinds(const float & dt) 
{
    checkForQuit();
}

void GameState::update(const float & dt)
{
    updateKeybinds(dt);
    player.update(dt);
}

void GameState::render(sf::RenderTarget * target)
{
    player.render(m_window);
}

void GameState::endState()
{
    std::cout << "The end of GameState\n";
}