#include "states/EditorState.hpp"
#include "states/StateData.hpp"
#include "GUI/PauseMenu.hpp"

EditorState::EditorState(std::shared_ptr<StateData> state_data)
    : State{ state_data }
    , m_tile_map{ std::unique_ptr<TileMap>{ new TileMap{} } }
{
    std::cout << "The start of EditorState\n";
    
    init_font();
    init_buttons();
    init_keybinds();
    init_pause_menu();
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
    m_buttons["EXIT"] = std::unique_ptr<gui::Button>{ new gui::Button{ m_window->getSize().x / 1.1, m_window->getSize().y / 1.1, 150, 50, m_font, "Exit" }};
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

void EditorState::init_pause_menu()
{
    m_pause_menu = std::unique_ptr<PauseMenu>{ new PauseMenu{ *m_window, m_font } };

    sf::Text quit_text;
    quit_text.setString("Quit");
    m_pause_menu->add_button("QUIT", quit_text,
        m_pause_menu->get_container().getPosition().x + m_pause_menu->get_container().getSize().x / 2 - quit_text.getGlobalBounds().width / 2,
        m_pause_menu->get_container().getPosition().y + m_pause_menu->get_container().getSize().y / 1.1 - quit_text.getGlobalBounds().height);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["PAUSE"])) && exit_delay_occurred()) {
        m_paused ? unpause_menu() : pause_menu();
    }
}

void EditorState::update_pause_menu_input()
{
    if (m_pause_menu->is_button_pressed("QUIT")) {
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
    update_exit_delay_time(dt);
    update_mouse_pos();
    update_input();

    if (m_paused) {
        m_pause_menu->update(m_mouse_pos_view);
        update_pause_menu_input();
    }
    else {
        m_tile_map->update(m_mouse_pos_view);
        update_mouse_pos_text();
        update_buttons(m_mouse_pos_view);
    }
}

void EditorState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_state_data->window();
    }

    m_tile_map->render(*target);
    render_buttons(*target);
    target->draw(m_mouse_pos_text);

    if (m_paused) {
        m_pause_menu->render(*target);
    }
}