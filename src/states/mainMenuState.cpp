#include "states/mainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states) :
    State(window, supportedKeys, states),
    m_mainPreview(sf::Vector2f(m_window->getSize()))
{
    std::cout << "The start of MainMenuState\n";
    
    initFont();
    initButtons();
    initKeybinds();
    m_mainPreview.setFillColor(sf::Color::Yellow);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::initFont()
{
    if (!m_font.loadFromFile("/home/mark/dev/cpp/work/LastHero/fonts/Dosis-Light.ttf")) {
        assert("MainMenuState::initFont::!loadFromFile");
        exit(1);
    }
}

void MainMenuState::initButtons()
{
    m_buttons["NEW_GAME"] = new Button(100, 100, 150, 50, &m_font, "New Game", 
        sf::Color(100, 100, 100, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200));

    m_buttons["EDITOR"] = new Button(100, 220, 150, 50, &m_font, "Editor", 
        sf::Color(100, 100, 100, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200));

    m_buttons["EXIT"] = new Button(100, 340, 150, 50, &m_font, "Exit", 
        sf::Color(100, 100, 100, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200));
}

void MainMenuState::updateButtons(sf::Vector2f mousePos) 
{
    for (const auto & button : m_buttons) {
        button.second->update(mousePos);
    }

    if (m_buttons["NEW_GAME"]->isPressed()) {
        m_states->push(new GameState(m_window, m_supportedKeys, m_states));
    }
    if (m_buttons["EDITOR"]->isPressed()) {
        // openEditor();
    }
    if (m_buttons["EXIT"]->isPressed()) {
        m_quit = true;
    }
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

void MainMenuState::updateKeybinds(const float & dt) 
{
    checkForQuit();
}

void MainMenuState::update(const float & dt)
{
    updateMousePos();
    updateKeybinds(dt);
    updateButtons(m_mousePosView);
}

void MainMenuState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    target->draw(m_mainPreview);
    renderButtons(target);
}

void MainMenuState::endState()
{
    std::cout << "The end of MainMenuState\n";
}