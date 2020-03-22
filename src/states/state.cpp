#include "states/state.hpp"

State::State(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys) :
    m_window(window),
    m_supportedKeys(supportedKeys),
    m_quit(false)
{

}

void State::checkForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"]))) {
        m_quit = true;
    }
}

const bool & State::getQuit() const {
    return m_quit;
}

void State::updateMousePos() 
{
    m_mousePosScreen = sf::Mouse::getPosition();
    m_mousePosWindow = sf::Mouse::getPosition(*m_window);
    m_mousePosView = m_window->mapPixelToCoords(sf::Mouse::getPosition()); //sf::View correct pos

    std::cout << m_mousePosView.x << "x" << m_mousePosView.y << "\n";
}

State::~State()
{
}