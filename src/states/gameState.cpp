#include "states/gameState.hpp"

GameState::GameState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys) :
    State(window, supportedKeys)
{
    std::cout << "The start of GameState\n";
    initKeybinds();
}

GameState::~GameState()
{
}

void GameState::initKeybinds()
{
    std::ifstream ifs("/home/mark/dev/cpp/work/LastHero/config/gameStateKeybinds.ini"); // Bad practice, necessary to change frough any filesystem/path;
    std::string key1 = "", key2 = "";

    if (ifs.is_open()) {
        while (ifs >> key1 >> key2) {
            m_keybinds[key1] = m_supportedKeys->at(key2);
        }
    } 
    ifs.close();
}

void GameState::updateKeybinds(const float & dt) 
{
    checkForQuit();
}

void GameState::update(const float & dt)
{
    updateKeybinds(dt);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_LEFT"]))) {
        player.move(dt, -1.0f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_RIGHT"]))) {
        player.move(dt, 1.0f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_UP"]))) {
        player.move(dt, 0.f, -1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_DOWN"]))) {
        player.move(dt, 0.f, 1.0f);
    }
}

void GameState::render(sf::RenderTarget * target)
{
    player.render(m_window);
}

void GameState::endState()
{
    std::cout << "The end of GameState\n";
}