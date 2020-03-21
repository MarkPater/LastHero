#include "game.hpp"

Game::Game()
{
    init();
}

Game::~Game()
{
    delete m_mainWindow;
}

void Game::init()
{
    m_mainWindow = new sf::RenderWindow(sf::VideoMode(1080, 720), "LastHero");
}

void Game::updateDt() 
{
    dt = dtClock.restart().asSeconds(); // ~0.001 for
}

void Game::update()
{

    while (m_mainWindow->pollEvent(m_sfEvent)) {
        if (m_sfEvent.type == sf::Event::Closed) {
            m_mainWindow->close();
        }
    }
    updateDt();
}

void Game::render()
{
    m_mainWindow->clear();
    m_mainWindow->display();
}

void Game::run()
{
    while (m_mainWindow->isOpen()) {
        update();
        render();
    }
}