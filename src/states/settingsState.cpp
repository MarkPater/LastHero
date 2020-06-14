#include "states/settingsState.hpp"

SettingsState::SettingsState(sf::RenderWindow * window, std::map<std::string, int> * supported_keys, std::stack<State *> * states)
    : State(window, supported_keys, states)
    , m_background(sf::Vector2f(m_window->getSize()))
    , m_video_modes(sf::VideoMode::getFullscreenModes())
{
    init_fonts();
    init_gui();
    init_settings();
    init_keybinds();
    init_background();
    init_mouse_pos_text();
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

void SettingsState::init_fonts()
{
    if (!m_font.loadFromFile(m_current_path + "/fonts/Dosis-Light.ttf")) {
        assert(false && "SettingsState::initFonts::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void SettingsState::init_background()
{
    m_background.setFillColor(sf::Color::Black);
}

void SettingsState::init_gui()
{
    m_buttons["BACK"] = new gui::Button(1365, 120, 150, 50, m_font, "Exit");
    m_buttons["BACK"]->set_button_colors(sf::Color(85, 10, 10, 100), sf::Color(110, 20, 20, 120), sf::Color(130, 30, 30, 140));
    m_buttons["APPLY"] = new gui::Button(1550, 120, 150, 50, m_font, "Apply", 40);
    m_buttons["APPLY"]->set_button_colors(sf::Color(10, 85, 10, 100), sf::Color(20, 110, 20, 120), sf::Color(30, 130, 30, 140));

    m_combo_boxes["RESOLUTION"] = new gui::ComboBox(m_font, 1440, 190, 200, 60);
    m_combo_boxes["RESOLUTION"]->add_items(from_video_modes_to_strings().data(), 8);
}

void SettingsState::init_settings()
{
    m_settings_text.setFont(m_font);
    m_settings_text.setCharacterSize(35);
    m_settings_text.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n");
}

void SettingsState::init_keybinds() 
{
    std::ifstream ifs(m_current_path + "/config/settingsStateKeybinds.ini");
    std::string action = "", key = "";

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supported_keys->at(key);
        }
    }
    ifs.close();
}

void SettingsState::init_mouse_pos_text()
{
    m_mouse_pos_text.setFont(m_font);
}

std::vector<std::string> SettingsState::from_video_modes_to_strings() const
{
    std::vector<std::string> strings{};

    for (int i = 0; i < m_video_modes.size(); ++i) {
        strings.push_back(std::to_string(m_video_modes[i].width) + "x" + std::to_string(m_video_modes[i].height));
    }

    return strings;
}

void SettingsState::update_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["BACK"]))) {
        end_state();
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
        end_state();
    }
    else if (m_buttons["APPLY"]->is_pressed()) {
        m_window->create(m_video_modes[m_combo_boxes["RESOLUTION"]->current_index()], "Test", sf::Style::Default);
    }
}

void SettingsState::update(float dt)
{
    update_input();
    update_mouse_pos();
    update_mouse_pos_text();
    update_gui(dt, m_mouse_pos_view);
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
    target->draw(m_settings_text);
    target->draw(m_mouse_pos_text);
}