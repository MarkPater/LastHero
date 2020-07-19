#include "states/EditorState.hpp"
#include "states/StateData.hpp"
#include "GUI/PauseMenu.hpp"
#include "map/TileMap.hpp"
#include "GraphicsSettings.hpp"

#include <sstream>

EditorState::EditorState(std::shared_ptr<StateData> state_data)
    : State{ state_data }
    , m_tile_rect{ 0, 0, m_state_data->grid_size(), m_state_data->grid_size() }
    , m_tile_delay_time{ -12 }
    , m_tile_max_delay_time{ 1.5F }
{
    std::cout << "EditorState::EditorState():\t" << "The start of EditorState" << "\n";
    
    init_font();
    init_gui();
    init_keybinds();
    init_pause_menu();
    init_mouse_pos_text();
}

EditorState::~EditorState()
{
    std::cout << "EditorState::~EditorState():\t" << "The end of EditorState" << "\n";
}

void EditorState::init_font()
{
    if (!m_font.loadFromFile(m_current_path + "/fonts/Dosis-Light.ttf")) {
        assert(false && "EditorState::init_font::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void EditorState::init_gui()
{
    m_tile_map = std::unique_ptr<TileMap>{ new TileMap{ m_state_data->grid_size(),
                                                        m_state_data->max_tile_map_size(),
                                                        m_state_data->current_path() }
    };

    m_texture_selector = std::unique_ptr<gui::TextureSelector>{ 
        new gui::TextureSelector{ 10, 10, 400, 400, m_state_data->grid_size(), m_tile_map->tile_map_texture_sheet(), m_font }
    };

    m_sidebar = std::unique_ptr<gui::Sidebar>{ new gui::Sidebar{ m_gfx_settings->window_bounds(), gui::WindowSide::Left, 85 } };

    m_selected_rect.setSize(sf::Vector2f{ m_state_data->grid_size(), m_state_data->grid_size() });
    m_selected_rect.setFillColor(sf::Color{ 200, 200, 200, 140 });
    m_selected_rect.setOutlineColor(sf::Color::Green);
    m_selected_rect.setOutlineThickness(1);
    m_selected_rect.setTexture(m_tile_map->tile_map_texture_sheet());
    m_selected_rect.setTextureRect(m_tile_rect);

    init_buttons();
}

void EditorState::init_buttons()
{
    m_buttons["EXIT"] = std::unique_ptr<gui::Button>{ 
        new gui::Button{ m_window->getSize().x / 1.1, m_window->getSize().y / 1.1, 150, 50, m_font, "Exit" }
    };
    m_buttons["EXIT"]->set_check_only_text(true);
    m_buttons["EXIT"]->set_button_colors();
}

void EditorState::init_keybinds()
{
    std::ifstream ifs{ m_current_path + "/config/editorStateKeybinds.ini" };
    std::string action{}, key{};

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supported_keys->at(key);
        }
        ifs.close();
    }
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
    m_rect_pos_text.setFont(m_font);
    m_rect_pos_text.setCharacterSize(13);
    m_rect_pos_text.setColor(sf::Color{ 255, 175, 250, 250});
}

bool EditorState::tile_delay_occurred()
{
    if (m_tile_delay_time >= m_tile_max_delay_time) {
        m_tile_delay_time = 0.f;
        return true;
    }
    return false;
}

void EditorState::update_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["PAUSE"])) && exit_delay_occurred()) {
        m_paused ? unpause_menu() : pause_menu();
    }
}

void EditorState::update_mouse_pos_text()
{
    m_rect_pos_text.setPosition(m_mouse_pos_view.x, m_mouse_pos_view.y - 40);

    std::stringstream ss;
    ss << m_mouse_pos_view.x << "x" << m_mouse_pos_view.y << "\n" << m_tile_rect.left << " " << m_tile_rect.top;
    m_rect_pos_text.setString(ss.str());
}

void EditorState::update_editor_input()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tile_delay_occurred()) {
        if (m_texture_selector->is_active()) {
            m_tile_rect = m_texture_selector->selected_tile_rect();
            m_selected_rect.setTextureRect(m_tile_rect);
        }
        else if (!m_sidebar->is_active()) {
            m_tile_map->add_tile(m_mouse_pos_grid.x / m_state_data->grid_size(),
                                 m_mouse_pos_grid.y / m_state_data->grid_size(),
                                 0, m_tile_rect);
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && tile_delay_occurred()) {
        if (m_texture_selector->is_active()) {

        }
        else {
            m_tile_map->remove_tile(m_mouse_pos_grid.x / m_state_data->grid_size(),
                                    m_mouse_pos_grid.y / m_state_data->grid_size(),
                                    0);
        }
    }
}

void EditorState::update_pause_menu_input()
{
    if (m_pause_menu->is_button_pressed("QUIT")) {
        end_state();
    }
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

void EditorState::update_gui(float dt)
{
    update_buttons(m_mouse_pos_view);

    m_tile_map->update(m_mouse_pos_view);
    m_texture_selector->update(dt, m_mouse_pos_window);
    m_sidebar->update(sf::Vector2f{ m_mouse_pos_window.x, m_mouse_pos_window.y });
    m_selected_rect.setPosition(sf::Vector2f{ m_mouse_pos_grid }); // move using grid type movement
}

void EditorState::update_tile_delay_time(float dt) {
    if (m_tile_delay_time < m_tile_max_delay_time) {
        m_tile_delay_time += 50 * dt;
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
        update_tile_delay_time(dt);
        update_gui(dt);
        update_editor_input();
        update_mouse_pos_text();
    }
}

void EditorState::render_buttons(sf::RenderTarget & target)
{
    for (const auto & button : m_buttons) {
        button.second->render(target);
    }
}

void EditorState::render_gui(sf::RenderTarget & target)
{   
    m_tile_map->render(target);
    m_texture_selector->render(target);
    m_sidebar->render(target);

    if (!m_texture_selector->is_active() && !m_sidebar->is_active()) {
        target.draw(m_selected_rect);
    }
    target.draw(m_rect_pos_text);

    render_buttons(target);
}

void EditorState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_state_data->window();
    }

    render_gui(*target);

    if (m_paused) {
        m_pause_menu->render(*target);
    }
}