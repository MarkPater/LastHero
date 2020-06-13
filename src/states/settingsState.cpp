#include "states/settingsState.hpp"

SettingsState::SettingsState(sf::RenderWindow * window, std::map<std::string, int> * supported_keys, std::stack<State *> * states)
    : State(window, supported_keys, states)
    , m_background(sf::Vector2f(m_window->getSize()))
{
    init_fonts();
    init_gui();
    initKeybinds();
    init_background();
}

SettingsState::~SettingsState()
{
    for (auto & button : m_buttons) {
        delete button.second;
    }

    for (auto & combo_box : m_combo_boxes) {
        delete combo_box.second;
    }
}

void SettingsState::init_background()
{
    m_background.setFillColor(sf::Color::Black);
}

void SettingsState::init_gui()
{
    m_buttons["BACK"] = new gui::Button(1365, 530, 150, 50, m_font, "Exit");
    m_buttons["BACK"]->set_button_colors(sf::Color(85, 10, 10, 100), sf::Color(110, 20, 20, 120), sf::Color(130, 30, 30, 140));
    m_buttons["APPLY"] = new gui::Button(1550, 530, 150, 50, m_font, "Apply", 40);
    m_buttons["APPLY"]->set_button_colors(sf::Color(10, 85, 10, 100), sf::Color(20, 110, 20, 120), sf::Color(30, 130, 30, 140));

    std::string resolutions[] = {"1080x1920", "800x600", "640x480"};
    m_combo_boxes["RESOLUTION"] = new gui::ComboBox(m_font, 1440, 600, 200, 60);
    m_combo_boxes["RESOLUTION"]->add_items(resolutions, 3);
}

void SettingsState::init_fonts()
{
    if (!m_font.loadFromFile(m_currentPath + "/fonts/Dosis-Light.ttf")) {
        assert(false && "SettingsState::initFonts::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void SettingsState::initKeybinds() 
{
    std::ifstream ifs(m_currentPath + "/config/settingsStateKeybinds.ini");
    std::string action = "", key = "";

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supportedKeys->at(key);
        }
    }
    ifs.close();
}

void SettingsState::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["BACK"]))) {
        endState();
    }
}

void SettingsState::update_gui(float dt, sf::Vector2f mouse_pos)
{
    for (const auto & button : m_buttons) {
        button.second->update(mouse_pos);
    }

    for (const auto & combo_box : m_combo_boxes) {
        combo_box.second->update(dt, mouse_pos);
    }

    if (m_buttons["BACK"]->is_pressed()) {
        endState();
    }
    else if (m_buttons["APPLY"]->is_pressed) {
        // save resolution
    }
}

void SettingsState::update(float dt)
{
    updateInput();
    updateMousePos();
    update_gui(dt, m_mousePosView);
}

void SettingsState::render_gui(sf::RenderTarget & target)
{
    for (const auto & button : m_buttons) {
        button.second->render(target);
    }

    for (const auto & combo_box : m_combo_boxes) {
        combo_box.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    target->draw(m_background);
    render_gui(*target);
}