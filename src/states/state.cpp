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

State::~State()
{
}