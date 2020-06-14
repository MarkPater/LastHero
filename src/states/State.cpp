#include "states/State.hpp"
#include <filesystem>

State::State(sf::RenderWindow * window, std::map<std::string, int> * supported_keys, std::stack<State *> * states)
    : m_window(window)
    , m_supported_keys(supported_keys)
    , m_states(states)
    , m_quit(false)
    , m_paused(false)
    , m_delay_time(0.f)
    , m_max_delay_time(10.f)
    , m_current_path(std::filesystem::current_path())
{
    init_mouse_pos_text();
}

State::~State()
{

}

void State::init_mouse_pos_text()
{
    m_mouse_pos_text.setCharacterSize(12);
    m_mouse_pos_text.setColor(sf::Color::White);
}

void State::update_mouse_pos_text()
{
    m_mouse_pos_text.setPosition(sf::Vector2f(m_mouse_pos_view.x, m_mouse_pos_view.y - 25));

    std::stringstream ss;
    ss << m_mouse_pos_view.x << "x" << m_mouse_pos_view.y;
    m_mouse_pos_text.setString(ss.str());
}

void State::pause_menu()
{
    m_paused = true;
}

void State::unpause_menu()
{
    m_paused = false;
}

void State::update_mouse_pos() 
{
    m_mouse_pos_screen = sf::Mouse::getPosition();
    m_mouse_pos_window = sf::Mouse::getPosition(*m_window);
    m_mouse_pos_view = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)); //sf::View correct pos
}

void State::update_delay_time(float dt)
{
    if (m_delay_time <= m_max_delay_time) {
        m_delay_time += 50.f * dt;
    }
}

bool State::delay_occurred()
{
    if (m_delay_time > m_max_delay_time) {
        m_delay_time = 0;
        return true;
    }

    return false;
}

const bool & State::get_quit() const 
{
    return m_quit;
}

void State::end_state()
{
    m_quit = true;
}