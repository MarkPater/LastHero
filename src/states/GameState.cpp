#include "states/GameState.hpp"
#include "map/TileMap.hpp"
#include "GUI/PauseMenu.hpp"
#include "Player.hpp"

GameState::GameState(std::shared_ptr<StateData> state_data)
    : State{ state_data }
{
    std::cout << "GameState::GameState():\t" << "The start of GameState" << "\n";

    init_keybinds();
    init_textures();
    init_font();
    init_pause_menu();
    init_players();
}

GameState::~GameState()
{
    std::cout << "GameState::~GameState():\t" << "The end of GameState" << "\n";
}

void GameState::init_keybinds()
{
    std::ifstream ifs{ m_current_path + "/config/gameStateKeybinds.ini" };
    std::string action{}, key{};

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supported_keys->at(key);
        }
        ifs.close();
    }
}

void GameState::init_textures()
{
    if (!m_textures["PLAYER_SHEET"].loadFromFile(m_current_path + "/resources/images/sprites/player/Player_sheet.png")) {
        assert(false && "GameState::init_textures::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void GameState::init_font()
{
    if (!m_font.loadFromFile(m_current_path + "/fonts/Dosis-Light.ttf")) {
        assert(false && "GameState::init_font::!loadFromFile");
        exit(EXIT_FAILURE);
    }
}

void GameState::init_pause_menu()
{
    m_pause_menu = std::unique_ptr<PauseMenu>{ new PauseMenu{ *m_window, m_font } };

    sf::Text quit_text;
    quit_text.setString("Quit");
    m_pause_menu->add_button("QUIT", quit_text,
        m_pause_menu->get_container().getPosition().x + m_pause_menu->get_container().getSize().x / 2 - quit_text.getGlobalBounds().width,
        m_pause_menu->get_container().getPosition().y + m_pause_menu->get_container().getSize().y / 1.1 - quit_text.getGlobalBounds().height);
}

void GameState::init_players()
{
    m_player = std::unique_ptr<Player>{ new Player{ 0, 0, m_textures["PLAYER_SHEET"] } };
}

void GameState::update_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["PAUSE"])) && exit_delay_occurred()) {
        m_paused ? unpause_menu() : pause_menu();
    }
}

void GameState::update_player_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_LEFT"]))) {
        m_player->move(-1.0f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_RIGHT"]))) {
        m_player->move(1.0f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_UP"]))) {
        m_player->move(0.f, -1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_DOWN"]))) {
        m_player->move(0.f, 1.0f);
    }
}

void GameState::update_pause_menu_input()
{
    if (m_pause_menu->is_button_pressed("QUIT")) {
        end_state();
    }
}

void GameState::update(float dt)
{
    update_exit_delay_time(dt);
    update_mouse_pos();
    update_input();

    if (m_paused) {
        m_pause_menu->update(m_mouse_pos_view);
        update_pause_menu_input();
    }
    else {
        update_player_input();
        m_player->update(dt);
    }
}

void GameState::render(sf::RenderTarget * target)
{
    if (!target) {
        target = m_window;
    }

    m_player->render(target);

    if (m_paused) {
        m_pause_menu->render(*target);
    }
}