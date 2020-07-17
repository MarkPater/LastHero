#include "Game.hpp"
#include "GraphicsSettings.hpp"
#include "states/StateData.hpp"
#include "states/MainMenuState.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>

Game::Game() 
    : m_gfx_settings{ std::shared_ptr<GraphicsSettings>(new GraphicsSettings{}) }
    , m_current_path{ std::filesystem::current_path() }
{
    std::cout << "The start of GameApp\n";
    init_graphics_settings();
    init_window();
    init_supported_keys();
    init_state_data();
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

void Game::init_graphics_settings()
{
    m_gfx_settings->load_from_file(m_current_path + "/config/gfx_settings.ini");
}

void Game::init_window()
{
    if (m_gfx_settings->is_fullscreen()) {
        m_main_window = new sf::RenderWindow(m_gfx_settings->window_bounds(), m_gfx_settings->window_title(),
                                             sf::Style::Fullscreen, m_gfx_settings->context_settings());
    }
    else {
        m_main_window = new sf::RenderWindow(m_gfx_settings->window_bounds(), m_gfx_settings->window_title(),
                                             sf::Style::Titlebar | sf::Style::Close, m_gfx_settings->context_settings());
        m_main_window->setPosition(sf::Vector2i{ 0, 0 });
    }
    m_main_window->setFramerateLimit(m_gfx_settings->framerate_limit());
    m_main_window->setVerticalSyncEnabled(m_gfx_settings->vertical_sync_enabled());
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

void Game::init_state_data()
{
    m_state_data = std::shared_ptr<StateData>{ new StateData{ m_gfx_settings, &m_supported_keys, &m_states, m_current_path, m_main_window } };
}

void Game::init_states()
{
    m_states.emplace(new MainMenuState{ m_state_data });
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