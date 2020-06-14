#include "states/EditorState.hpp"

EditorState::EditorState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states)
    : State(window, supportedKeys, states)
{
    std::cout << "The start of EditorState\n";
    
    init_font();
    init_buttons();
    init_keybinds();
    init_mouse_pos_text();
}

EditorState::~EditorState()
{
}

void EditorState::init_font()
{
    if (!m_font.loadFromFile(m_current_path + "/fonts/Dosis-Light.ttf")) {
        assert(false && "EditorState::init_font::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void EditorState::init_buttons()
{
    m_buttons["EXIT"] = new gui::Button(885, 515, 150, 50, m_font, "Exit");
    m_buttons["EXIT"]->set_check_only_text(true);
    m_buttons["EXIT"]->set_button_colors();
}

void EditorState::init_keybinds()
{
    std::ifstream ifs(m_current_path + "/config/editorStateKeybinds.ini");
    std::string action = "", key = "";

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supported_keys->at(key);
        }
    } 
    ifs.close();
}

void EditorState::init_mouse_pos_text()
{
    m_mouse_pos_text.setFont(m_font);
}

void EditorState::update_buttons(sf::Vector2f mousePos)
{
    for (const auto & button : m_buttons) {
        button.second->update(mousePos);
    }

    if (m_buttons["EXIT"]->is_pressed()) {
        end_state();
    }
}

void EditorState::update_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"]))) {
        end_state();
    }
}

void EditorState::render_buttons(sf::RenderTarget & target)
{
    for (const auto & button : m_buttons) {
        button.second->render(target);
    }
}

void EditorState::update(float dt)
{
    update_input();
    update_mouse_pos();
    update_mouse_pos_text();
    update_buttons(m_mouse_pos_view);
}

void EditorState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    render_buttons(*target);
    target->draw(m_mouse_pos_text);
}