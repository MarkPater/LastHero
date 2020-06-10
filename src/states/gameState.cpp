#include "states/gameState.hpp"

GameState::GameState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states)
    : State(window, supportedKeys, states)
{
    std::cout << "The start of GameState\n";
    initKeybinds();
    initTextures();
    initFont();
    initPauseMenu();
    initPlayers();
}

GameState::~GameState()
{
    delete m_player;
    delete m_pauseMenu;
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

void GameState::initFont()
{
    if (!m_font.loadFromFile(m_currentPath + "/fonts/Dosis-Light.ttf")) {
        assert(false && "GameState::initFont::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void GameState::initPauseMenu()
{
    m_pauseMenu = new PauseMenu(*m_window, m_font);

    sf::Text quitText;
    quitText.setString("Quit");
    m_pauseMenu->addButton("QUIT", quitText,
        m_pauseMenu->getContainer().getPosition().x + m_pauseMenu->getContainer().getSize().x / 2 - quitText.getGlobalBounds().width,
        m_pauseMenu->getContainer().getPosition().y + m_pauseMenu->getContainer().getSize().y / 1.1 - quitText.getGlobalBounds().height);
}

void GameState::initPlayers()
{
    m_player = new Player(0, 0, m_textures["PLAYER_SHEET"]);
}

void GameState::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["PAUSE"])) && delayOccurred()) {
        if (!m_paused) {
            pauseMenu();
        }
        else {
            unpauseMenu();
        }
    }
}

void GameState::updatePlayerInput()
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
}

void GameState::updatePauseMenuButtons()
{
    if (m_pauseMenu->isButtonPressed("QUIT")) {
        endState();
    }
}

void GameState::update(float dt)
{
    updateDelayTime(dt);
    updateMousePos();
    updateInput();

    if (!m_paused) {
        updatePlayerInput();
        m_player->update(dt);
    }
    else {
        m_pauseMenu->update(m_mousePosView);
        updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    m_player->render(target);

    if (m_paused) {
        m_pauseMenu->render(*target);
    }
}