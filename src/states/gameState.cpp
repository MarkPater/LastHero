#include "states/gameState.hpp"

GameState::GameState(sf::RenderWindow * window, std::map<std::string, int> * supported_keys, std::stack<State *> * states)
    : State(window, supported_keys, states)
{
    std::cout << "The start of GameState\n";
    init_keybinds();
    init_textures();
    init_font();
    init_pause_menu();
    init_players();
}

GameState::~GameState()
{
    delete m_player;
    delete m_pause_menu;
}

void GameState::init_keybinds()
{
    std::ifstream ifs(m_current_path + "/config/gameStateKeybinds.ini");
    std::string action = "", key = "";

    if (ifs.is_open()) {
        while (ifs >> action >> key) {
            m_keybinds[action] = m_supported_keys->at(key);
        }
    } 
    ifs.close();
}

void GameState::init_textures()
{
    if (!m_textures["PLAYER_SHEET"].loadFromFile(m_current_path + "/resources/images/sprites/player/Player_sheet.png")) {
        assert(false && "GameState::init_textures::!lodaFromFile");
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
    m_pause_menu = new PauseMenu(*m_window, m_font);

    sf::Text quitText;
    quitText.setString("Quit");
    m_pause_menu->add_button("QUIT", quitText,
        m_pause_menu->get_container().getPosition().x + m_pause_menu->get_container().getSize().x / 2 - quitText.getGlobalBounds().width,
        m_pause_menu->get_container().getPosition().y + m_pause_menu->get_container().getSize().y / 1.1 - quitText.getGlobalBounds().height);
}

void GameState::init_players()
{
    m_player = new Player(0, 0, m_textures["PLAYER_SHEET"]);
}

void GameState::update_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["PAUSE"])) && delay_occurred()) {
        if (!m_paused) {
            pause_menu();
        }
        else {
            unpause_menu();
        }
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

void GameState::update_pause_menu_buttons()
{
    if (m_pause_menu->is_button_pressed("QUIT")) {
        end_state();
    }
}

void GameState::update(float dt)
{
    update_delay_time(dt);
    update_mouse_pos();
    update_input();

    if (!m_paused) {
        update_player_input();
        m_player->update(dt);
    }
    else {
        m_pause_menu->update(m_mouse_pos_view);
        update_pause_menu_buttons();
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