#include "states/mainMenuState.hpp"
#include "states/editorState.hpp"
#include "states/gameState.hpp"
#include "states/settingsState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states)
    : State(window, supportedKeys, states)
    , m_background(sf::Vector2f(m_window->getSize()))
{
    std::cout << "The start of MainMenuState\n";
    
    initFonts();
    init_gui();
    initKeybinds();
    initMousePos();
    initBackground();
}

MainMenuState::~MainMenuState()
{
    for (auto & button : m_buttons) {
        delete button.second;
    }
}

void MainMenuState::initFonts()
{
    if (!m_font.loadFromFile(m_currentPath + "/fonts/Dosis-Light.ttf")) {
        assert(false && "MainMenuState::initFont::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void MainMenuState::init_gui()
{    
    m_buttons["GAME_STATE"] = new gui::Button(1400, 280, 150, 50, m_font, "New Game");
    m_buttons["SETTINGS_STATE"] = new gui::Button(1400, 430, 150, 50, m_font, "Settings");
    m_buttons["EDITOR_STATE"] = new gui::Button(1400, 580, 150, 50, m_font, "Editor");
    m_buttons["EXIT"] = new gui::Button(1400, 730, 150, 50, m_font, "Exit");

    for (auto & button : m_buttons) {
        button.second->set_check_only_text(true);
        button.second->set_button_colors();
        button.second->set_outline_text_colors(sf::Color(15, 125, 120, 30), sf::Color(50, 10, 85, 225), sf::Color(135, 30, 30, 255));
        button.second->set_text_colors(sf::Color(250, 40, 40, 250), sf::Color(20, 100, 185, 225), sf::Color(135, 130, 130, 255));
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

void MainMenuState::initMousePos()
{
    m_mousePosText.setFont(m_font);
    m_mousePosText.setCharacterSize(12);
    m_mousePosText.setColor(sf::Color::White);
    m_mousePosText.setStyle(sf::Text::Italic);
}

void MainMenuState::initBackground()
{
    if (!m_backgroundTexture.loadFromFile(m_currentPath + "/resources/images/backgrounds/bg1.jpg")) {
        assert(false && "MainMenuState::init::!loadFromFile");
        exit(EXIT_FAILURE);
    }

    m_background.setTexture(&m_backgroundTexture);
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

void MainMenuState::updateButtons(sf::Vector2f mousePos)
{
    for (const auto & button : m_buttons) {
        button.second->update(mousePos);
    }

    if (m_buttons["GAME_STATE"]->is_pressed()) {
        m_states->push(new GameState(m_window, m_supportedKeys, m_states));
    }
    else if (m_buttons["EDITOR_STATE"]->is_pressed()) {
        m_states->push(new EditorState(m_window, m_supportedKeys, m_states));
    }
    else if (m_buttons["SETTINGS_STATE"]->is_pressed()) {
        m_states->push(new SettingsState(m_window, m_supportedKeys, m_states));
    }
    else if (m_buttons["EXIT"]->is_pressed()) {
        endState();
    }
}

void MainMenuState::update(float dt)
{
    updateInput();
    updateMousePos();
    updateMousePosText();
    updateButtons(m_mousePosView);
}

void MainMenuState::renderButtons(sf::RenderTarget & target)
{
    for (const auto & button : m_buttons) {
        button.second->render(target);
    }
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