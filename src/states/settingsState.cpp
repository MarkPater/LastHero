#include "states/settingsState.hpp"
#include "button.hpp"

SettingsState::SettingsState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states)
    : State(window, supportedKeys, states)
    , m_background(sf::Vector2f(m_window->getSize()))
{
    initFonts();
    initButtons();
    initKeybinds();
    initBackground();
}

SettingsState::~SettingsState()
{
    for (auto & button : m_buttons) {
        delete button.second;
    }
}

void SettingsState::initBackground()
{
    m_background.setFillColor(sf::Color::Black);
}

void SettingsState::initFonts()
{
    if (!m_font.loadFromFile(m_currentPath + "/fonts/Dosis-Light.ttf")) {
        assert(false && "SettingsState::initFonts::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void SettingsState::initButtons()
{
    m_buttons["EXIT"] = new Button(1400, 730, 150, 50, &m_font, "Exit", 50, 
        sf::Color(0, 200, 0, 250), sf::Color(250, 135, 50, 200), sf::Color(50, 250, 165, 250),
        sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));
}

void SettingsState::initKeybinds() 
{
    std::ifstream ifs(m_currentPath + "/config/settingsStateKeybinds.ini");
    std::string action = "", key = "";

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supportedKeys->at(key);
        }
    }
    ifs.close();
}

void SettingsState::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["EXIT"]))) {
        endState();
    }
}

void SettingsState::updateButtons(sf::Vector2f mousePos)
{
    for (const auto & button : m_buttons) {
        button.second->update(mousePos);
    }

    if (m_buttons["EXIT"]->isPressed()) {
        endState();
    }
}

void SettingsState::update(float dt)
{
    updateInput();
    updateMousePos();
    updateButtons(m_mousePosView);
}

void SettingsState::renderButtons(sf::RenderTarget & target)
{
    for (const auto & button : m_buttons) {
        button.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    target->draw(m_background);
    renderButtons(*target);
}