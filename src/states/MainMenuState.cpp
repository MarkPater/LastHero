#include "states/MainMenuState.hpp"
#include "states/EditorState.hpp"
#include "states/GameState.hpp"
#include "states/SettingsState.hpp"
#include "states/StateData.hpp"

MainMenuState::MainMenuState(std::shared_ptr<StateData> state_data)
    : State{ state_data }
    , m_background{ sf::Vector2f{ m_window->getSize() } }
{
    std::cout << "MainMenuState::MainMenuState():\t" << "The start of MainMenuState" << "\n";
    
    init_fonts();
    init_gui();
    init_keybinds();
    init_background();
    init_mouse_pos_text();
}

MainMenuState::~MainMenuState()
{
    for (auto & button : m_buttons) {
        delete button.second;
    }
    std::cout << "MainMenuState::~MainMenuState():\t" << "The end of MainMenuState" << "\n";
}

void MainMenuState::init_fonts()
{
    if (!m_font.loadFromFile(m_current_path + "/fonts/Dosis-Light.ttf")) {
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

void MainMenuState::init_keybinds()
{
    std::ifstream ifs(m_current_path + "/config/mainMenuStateKeybinds.ini");
    std::string action = "", key = "";

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supported_keys->at(key);
        }
    }
    ifs.close();
}

void MainMenuState::init_background()
{
    if (!m_background_texture.loadFromFile(m_current_path + "/resources/images/backgrounds/bg1.jpg")) {
        assert(false && "MainMenuState::init::!loadFromFile");
        exit(EXIT_FAILURE);
    }

    m_background.setTexture(&m_background_texture);
}

void MainMenuState::init_mouse_pos_text()
{
    m_mouse_pos_text.setFont(m_font);
}

void MainMenuState::update_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["EXIT"]))) {
        end_state();
    }
}

void MainMenuState::update_buttons(sf::Vector2f mousePos)
{
    for (const auto & button : m_buttons) {
        button.second->update(mousePos);
    }

    if (m_buttons["GAME_STATE"]->is_pressed()) {
        m_states->push(new GameState(m_state_data));
    }
    else if (m_buttons["EDITOR_STATE"]->is_pressed()) {
        m_states->push(new EditorState(m_state_data));
    }
    else if (m_buttons["SETTINGS_STATE"]->is_pressed()) {
        m_states->push(new SettingsState(m_state_data));
    }
    else if (m_buttons["EXIT"]->is_pressed()) {
        end_state();
    }
}

void MainMenuState::update(float dt)
{
    update_input();
    update_mouse_pos();
    update_mouse_pos_text();
    update_buttons(m_mouse_pos_view);
}

void MainMenuState::render_buttons(sf::RenderTarget & target)
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
    render_buttons(*target);
    target->draw(m_mouse_pos_text);
}