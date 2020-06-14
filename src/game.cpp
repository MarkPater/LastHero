#include "game.hpp"
#include <filesystem>

Game::Game() :
    m_window_title("LastHero"),
    m_window_bounds(1080, 720),
    m_is_fullscreen(false),
    m_framerate_limit(60),
    m_current_path(std::filesystem::current_path())
{
    std::cout << "The start of GameApp\n";
    init_window();
    init_supported_keys();
    init_states();
}

Game::~Game()
{
    while (!m_states.empty()) {
        delete m_states.top();
        m_states.pop();
    }
    delete m_main_window;
}

void Game::init_window()
{
    std::ifstream ifs(m_current_path + "/config/window.ini");
    m_video_modes = sf::VideoMode::getFullscreenModes();

    if (ifs.is_open()) {
        std::getline(ifs, m_window_title);
        ifs >> m_window_bounds.width >> m_window_bounds.height;
        ifs >> m_framerate_limit;
        ifs >> m_is_fullscreen;
    }
    ifs.close();

    if (m_is_fullscreen) {
        m_main_window = new sf::RenderWindow(m_video_modes[0], m_window_title, sf::Style::Fullscreen);
    }
    else {
        m_main_window = new sf::RenderWindow(m_window_bounds, m_window_title, sf::Style::Titlebar | sf::Style::Close);
        m_main_window->setPosition(sf::Vector2i(0, 0));
    }
    m_main_window->setFramerateLimit(m_framerate_limit);
}

void Game::init_supported_keys()
{
    std::ifstream ifs(m_current_path + "/config/supportedKeys.ini");
    std::string key = "";
    int key_value = 0;

    if (ifs.is_open()) {
        while (ifs >> key >> key_value) {
            m_supported_keys[key] = key_value;
        }
    }
    ifs.close();
}

void Game::init_states()
{
    m_states.emplace(new MainMenuState(m_main_window, &m_supported_keys, &m_states));
}

void Game::update_dt() 
{
    m_dt = m_dt_clock.restart().asSeconds(); // ~0.001 for you
}

void Game::update_sfml_events() 
{
    while (m_main_window->pollEvent(m_sf_event)) {
        if (m_sf_event.type == sf::Event::Closed) {
            m_main_window->close();
        }
    }
}

void Game::update()
{
    update_sfml_events();
    update_dt();

    if (!m_states.empty()) {
        m_states.top()->update(m_dt);
        if (m_states.top()->get_quit()) {
            delete m_states.top();
            m_states.pop();
        }
    }
    else {
        end_application();
    }
}

void Game::render()
{
    m_main_window->clear();
    if (!m_states.empty()) {
        m_states.top()->render(m_main_window);
    }
    m_main_window->display();
}

void Game::run()
{
    while (m_main_window->isOpen()) {
        update();
        render();
    }
}

void Game::end_application()
{
    std::cout << "The end of GameApp\n";
    m_main_window->close();
}