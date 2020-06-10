#include "states/editorState.hpp"

EditorState::EditorState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states)
    : State(window, supportedKeys, states)
{
    std::cout << "The start of EditorState\n";
    
    initFont();
    initButtons();
    initKeybinds();
    initMousePos();
}

EditorState::~EditorState()
{
}

void EditorState::initFont()
{
    if (!m_font.loadFromFile(m_currentPath + "/fonts/Dosis-Light.ttf")) {
        assert(false && "EditorState::initFont::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void EditorState::initButtons()
{
    m_buttons["EXIT"] = new Button(885, 515, 150, 50, &m_font, "Exit", 50,
        sf::Color(0, 200, 0, 250), sf::Color(250, 135, 50, 200), sf::Color(50, 250, 165, 250),
        sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));
}

void EditorState::initKeybinds()
{
    std::ifstream ifs(m_currentPath + "/config/editorStateKeybinds.ini");
    std::string action = "", key = "";

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supportedKeys->at(key);
        }
    } 
    ifs.close();
}

void EditorState::initMousePos()
{
    m_mousePosText.setFont(m_font);
    m_mousePosText.setCharacterSize(12);
    m_mousePosText.setColor(sf::Color::White);
    m_mousePosText.setStyle(sf::Text::Italic);
}

void EditorState::updateButtons(sf::Vector2f mousePos)
{
    for (const auto & button : m_buttons) {
        button.second->update(mousePos);
    }

    if (m_buttons["EXIT"]->isPressed()) {
        endState();
    }
}

void EditorState::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"]))) {
        endState();
    }
}

void EditorState::updateMousePosText()
{
    m_mousePosText.setPosition(m_mousePosView.x, m_mousePosView.y - 25);

    std::stringstream ss;
    ss << m_mousePosView.x << "x" << m_mousePosView.y;
    m_mousePosText.setString(ss.str());
}

void EditorState::renderButtons(sf::RenderTarget & target)
{
    for (const auto & button : m_buttons) {
        button.second->render(target);
    }
}

void EditorState::update(float dt)
{
    updateInput();
    updateMousePos();
    updateMousePosText();
    updateButtons(m_mousePosView);
}

void EditorState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    renderButtons(*target);
    target->draw(m_mousePosText);
}