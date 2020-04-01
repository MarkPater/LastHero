#include "states/state.hpp"
#include <filesystem>

State::State(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states) :
    m_window(window),
    m_supportedKeys(supportedKeys),
    m_quit(false),
    m_states(states),
    m_currentPath(std::filesystem::current_path())
{

}

const bool & State::getQuit() const 
{
    return m_quit;
}

void State::endState()
{
    m_quit = true;
}

void State::updateMousePos() 
{
    m_mousePosScreen = sf::Mouse::getPosition();
    m_mousePosWindow = sf::Mouse::getPosition(*m_window);
    m_mousePosView = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)); //sf::View correct pos

    //std::cout << m_mousePosView.x << "x" << m_mousePosView.y << "\n";
}

State::~State()
{
}