#include "states/state.hpp"
#include <filesystem>

State::State(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states)
    : m_window(window)
    , m_supportedKeys(supportedKeys)
    , m_states(states)
    , m_quit(false)
    , m_paused(false)
    , m_delayTime(0.f)
    , m_maxDelayTime(10.f)
    , m_currentPath(std::filesystem::current_path())
{
}

State::~State()
{

}

void State::pauseMenu()
{
    m_paused = true;
}

void State::unpauseMenu()
{
    m_paused = false;
}

void State::updateMousePos() 
{
    m_mousePosScreen = sf::Mouse::getPosition();
    m_mousePosWindow = sf::Mouse::getPosition(*m_window);
    m_mousePosView = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)); //sf::View correct pos
}

void State::updateDelayTime(float dt)
{
    if (m_delayTime <= m_maxDelayTime) {
        m_delayTime += 50.f * dt;
    }
}

bool State::delayOccurred()
{
    if (m_delayTime > m_maxDelayTime) {
        m_delayTime = 0;
        return true;
    }

    return false;
}

const bool & State::getQuit() const 
{
    return m_quit;
}

void State::endState()
{
    m_quit = true;
}