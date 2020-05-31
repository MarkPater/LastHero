#include "states/gameState.hpp"

GameState::GameState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states)
    : State(window, supportedKeys, states)
{
    std::cout << "The start of GameState\n";
    initKeybinds();
    initTextures();
    initPlayers();
}

GameState::~GameState()
{
    delete m_player;
}

void GameState::initKeybinds()
{
    std::ifstream ifs(m_currentPath + "/config/gameStateKeybinds.ini");
    std::string action = "", key = "";

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supportedKeys->at(key);
        }
    } 
    ifs.close();
}

void GameState::initTextures()
{
    if (!m_textures["PLAYER_SHEET"].loadFromFile(m_currentPath + "/resources/images/sprites/player/Player_sheet.png")) {
        assert(false && "GameState::initTextures::!lodaFromFile");
        exit(EXIT_FAILURE);
    }
}

void GameState::initPlayers()
{
    m_player = new Player(0, 0, m_textures["PLAYER_SHEET"]);
}

void GameState::updateInput() 
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_LEFT"]))) {
        m_player->move(-1.0f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_RIGHT"]))) {
        m_player->move(1.0f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_UP"]))) {
        m_player->move(0.f, -1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_DOWN"]))) {
        m_player->move(0.f, 1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"]))) {
        endState();
    }
}

void GameState::update(const float & dt)
{
    updateMousePos();
    updateInput();

    m_player->update(dt);
}

void GameState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    m_player->render(target);
}