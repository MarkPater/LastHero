#include "states/mainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys) :
    State(window, supportedKeys),
    m_mainPreview(sf::Vector2f(m_window->getSize()))
{
    std::cout << "The start of MainMenuState\n";
    
    initFont();
    initKeybinds();
    m_mainPreview.setFillColor(sf::Color::Yellow);

    m_gameStateButton = new Button(100, 100, 150, 50, &m_font, "New Game", 
        sf::Color(70, 70, 70, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200));
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

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("/home/mark/dev/cpp/work/LastHero/config/gameStateKeybinds.ini"); // Bad practice, necessary to change frough any filesystem/path;
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
    m_gameStateButton->update(m_mousePosView);
}

void MainMenuState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    target->draw(m_mainPreview);
    m_gameStateButton->render(target);
}

void MainMenuState::endState()
{
    std::cout << "The end of MainMenuState\n";
}