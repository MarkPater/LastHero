#include "states/gameState.hpp"

GameState::GameState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states) :
    State(window, supportedKeys, states)
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
}

void GameState::update(const float & dt)
{
    updateMousePos();
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"]))) {
        endState();
    }
}

void GameState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    player.render(m_window);
}