#include "game.hpp"

Game::Game()
{
    initWindow();
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
    std::ifstream ifs("/home/mark/dev/cpp/work/LastHero/config/window.ini");
    std::string windowTitle = "Game";
    int width = 1080, height = 720, framerateLimit = 60;

    if (ifs.is_open()) {
        std::getline(ifs, windowTitle);
        ifs >> width >> height >> framerateLimit;
        ifs.close();
    }

    m_mainWindow = new sf::RenderWindow(sf::VideoMode(width, height), windowTitle);
    m_mainWindow->setFramerateLimit(framerateLimit);
}

void Game::initStates()
{
    m_states.emplace(new GameState(m_mainWindow));
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
    std::cout << "The end of application\n";
    m_mainWindow->close();
}