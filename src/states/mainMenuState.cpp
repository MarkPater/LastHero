#include "states/mainMenuState.hpp"
#include "states/editorState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states)
    : State(window, supportedKeys, states)
    , m_background(sf::Vector2f(m_window->getSize()))
{
    std::cout << "The start of MainMenuState\n";
    
    initFont();
    initButtons();
    initKeybinds();
    initMousePos();
    initBackground();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::initFont()
{
    if (!m_font.loadFromFile(m_currentPath + "/fonts/Dosis-Light.ttf")) {
        assert(false && "MainMenuState::initFont::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void MainMenuState::initButtons()
{
    m_buttons["GAME_STATE"] = new Button(1400, 280, 150, 50, &m_font, "New Game", 50,
        sf::Color(0, 200, 0, 255), sf::Color(250, 135, 50, 200), sf::Color(50, 250, 165, 250),
        sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));

    m_buttons["EDITOR_STATE"] = new Button(1400, 430, 150, 50, &m_font, "Editor", 50,
        sf::Color(0, 200, 0, 250), sf::Color(250, 135, 45, 200), sf::Color(50, 250, 165, 250),
        sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));

    m_buttons["EXIT"] = new Button(1400, 580, 150, 50, &m_font, "Exit", 50,
        sf::Color(0, 200, 0, 250), sf::Color(250, 135, 50, 200), sf::Color(50, 250, 165, 250),
        sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));
}

void MainMenuState::initBackground()
{
    if (!m_backgroundTexture.loadFromFile(m_currentPath + "/resources/images/backgrounds/bg1.jpg")) {
        assert(false && "MainMenuState::init::!loadFromFile");
        exit(EXIT_FAILURE);
    }

    m_background.setTexture(&m_backgroundTexture);
}

void MainMenuState::initMousePos()
{
    m_mousePosText.setFont(m_font);
    m_mousePosText.setCharacterSize(12);
    m_mousePosText.setColor(sf::Color::White);
    m_mousePosText.setStyle(sf::Text::Italic);
}

void MainMenuState::updateButtons(sf::Vector2f mousePos)
{
    for (const auto & button : m_buttons) {
        button.second->update(mousePos);
    }

    if (m_buttons["GAME_STATE"]->isPressed()) {
        m_states->push(new GameState(m_window, m_supportedKeys, m_states));
    }
    else if (m_buttons["EDITOR_STATE"]->isPressed()) {
        m_states->push(new EditorState(m_window, m_supportedKeys, m_states));
    }
    else if (m_buttons["EXIT"]->isPressed()) {
        endState();
    }
}

void MainMenuState::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["EXIT"]))) {
        endState();
    }
}

void MainMenuState::updateMousePosText()
{
    m_mousePosText.setPosition(m_mousePosView.x, m_mousePosView.y - 25);

    std::stringstream ss;
    ss << m_mousePosView.x << "x" << m_mousePosView.y;
    m_mousePosText.setString(ss.str());
}

void MainMenuState::renderButtons(sf::RenderTarget & target)
{
    for (const auto & button : m_buttons) {
        button.second->render(target);
    }
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs(m_currentPath + "/config/mainMenuStateKeybinds.ini");
    std::string action = "", key = "";

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supportedKeys->at(key);
        }
    }
    ifs.close();
}

void MainMenuState::update(const float & dt)
{
    updateInput();
    updateMousePos();
    updateMousePosText();
    updateButtons(m_mousePosView);
}

void MainMenuState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    target->draw(m_background);
    renderButtons(*target);
    target->draw(m_mousePosText);
}