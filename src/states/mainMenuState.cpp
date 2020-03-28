#include "states/mainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states) :
    State(window, supportedKeys, states),
    m_background(sf::Vector2f(m_window->getSize()))
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
    if (!m_font.loadFromFile("/home/mark/dev/cpp/work/LastHero/fonts/Dosis-Light.ttf")) {
        assert(false && "MainMenuState::initFont::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void MainMenuState::initButtons()
{
    m_buttons["NEW_GAME"] = new Button(1400, 280, 150, 50, &m_font, "New Game",
        sf::Color(100, 100, 100, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 250));

    m_buttons["EDITOR_STATE"] = new Button(1400, 400, 150, 50, &m_font, "Editor",
        sf::Color(100, 100, 100, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 250));

    m_buttons["EXIT"] = new Button(1400, 520, 150, 50, &m_font, "Exit",
        sf::Color(100, 100, 100, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 250));
}

void MainMenuState::initBackground()
{
    if (!m_backgroundTexture.loadFromFile("/home/mark/dev/cpp/work/LastHero/resources/images/backgrounds/bg1.jpg")) {
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

    if (m_buttons["NEW_GAME"]->isPressed()) {
        m_states->push(new GameState(m_window, m_supportedKeys, m_states));
    }
    if (m_buttons["EDITOR_STATE"]->isPressed()) {
        // openEditor();
    }
    if (m_buttons["EXIT"]->isPressed()) {
        m_quit = true;
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

void MainMenuState::renderButtons(sf::RenderTarget * target)
{
    for (const auto & button : m_buttons) {
        button.second->render(target);
    }
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("/home/mark/dev/cpp/work/LastHero/config/mainMenuStateKeybinds.ini"); // Bad practice, necessary to change frough any filesystem/path;
    std::string key1 = "", key2 = "";

    if (ifs.is_open()) {
        while (ifs >> key1 >> key2) {
            m_keybinds[key1] = m_supportedKeys->at(key2);
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
    renderButtons(target);
    target->draw(m_mousePosText);
}