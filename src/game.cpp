#include "game.hpp"

Game::Game() :
    m_windowTitle("LastHero"),
    m_windowBounds(1080, 720),
    m_isFullscreen(false),
    m_framerateLimit(60)
{
    std::cout << "The start of GameApp\n";
    initWindow();
    initSupportedKeys();
    initStates();
}

Game::~Game()
{
    while (!m_states.empty()) {
        delete m_states.top();
        m_states.pop();
    }
    delete m_mainWindow;
}

void Game::initWindow()
{
    std::ifstream ifs("/home/mark/dev/cpp/work/LastHero/config/window.ini"); // Bad practice, necessary to change frough any filesystem/path;
    m_videoModes = sf::VideoMode::getFullscreenModes();

    if (ifs.is_open()) {
        std::getline(ifs, m_windowTitle);
        ifs >> m_windowBounds.width >> m_windowBounds.height;
        ifs >> m_framerateLimit;
        ifs >> m_isFullscreen;
    }
    ifs.close();

    if (m_isFullscreen) {
        m_mainWindow = new sf::RenderWindow(m_videoModes[0], m_windowTitle, sf::Style::Fullscreen);
    }
    else {
        m_mainWindow = new sf::RenderWindow(m_windowBounds, m_windowTitle, sf::Style::Titlebar | sf::Style::Close);
    }
    m_mainWindow->setFramerateLimit(m_framerateLimit);
}

void Game::initSupportedKeys()
{
    std::ifstream ifs("/home/mark/dev/cpp/work/LastHero/config/supportedKeys.ini"); // Bad practice, necessary to change frough any filesystem/path;
    std::string key = "";
    int key_value = 0;

    if (ifs.is_open()) {
        while (ifs >> key >> key_value) {
            m_supportedKeys[key] = key_value;
        }
    }
    ifs.close();

    for (const auto & el : m_supportedKeys) {
        std::cout << el.first << " -> " << el.second << "\n";
    }
}

void Game::initStates()
{
    m_states.emplace(new MainMenuState(m_mainWindow, &m_supportedKeys, &m_states));
}

void Game::updateDt() 
{
    m_dt = m_dtClock.restart().asSeconds(); // ~0.001 for you
}

void Game::updateSfmlEvents() 
{
    while (m_mainWindow->pollEvent(m_sfEvent)) {
        if (m_sfEvent.type == sf::Event::Closed) {
            m_mainWindow->close();
        }
    }
}

void Game::update()
{
    updateSfmlEvents();
    updateDt();

    if (!m_states.empty()) {
        m_states.top()->update(m_dt);
        if (m_states.top()->getQuit()) {
            m_states.top()->endState();
            delete m_states.top();
            m_states.pop();
        }
    }
    else {
        endApplication();
    }
}

void Game::render()
{
    m_mainWindow->clear();
    if (!m_states.empty()) {
        m_states.top()->render(m_mainWindow);
    }
    m_mainWindow->display();
}

void Game::run()
{
    while (m_mainWindow->isOpen()) {
        update();
        render();
    }
}

void Game::endApplication()
{
    std::cout << "The end of GameApp\n";
    m_mainWindow->close();
}