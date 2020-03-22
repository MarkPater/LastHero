#include "states/mainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys) :
    State(window, supportedKeys),
    m_mainPreview(sf::Vector2f(m_window->getSize()))
{
    std::cout << "The start of MainMenuState\n";
    initKeybinds();
    m_mainPreview.setFillColor(sf::Color::Yellow);
}

MainMenuState::~MainMenuState()
{
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
    updateKeybinds(dt);
}

void MainMenuState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    target->draw(m_mainPreview);
}

void MainMenuState::endState()
{
    std::cout << "The end of MainMenuState\n";
}