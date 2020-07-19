#include "states/State.hpp"
#include "states/StateData.hpp"
#include "GraphicsSettings.hpp"

#include <filesystem>

State::State(std::shared_ptr<StateData> state_data)
    : m_state_data{ std::move(state_data) }
    , m_supported_keys{ m_state_data->supported_keys() }
    , m_states{ m_state_data->states() }
    , m_gfx_settings{ std::move(m_state_data->gfx_settings()) }
    , m_current_path{ m_state_data->current_path() }
    , m_window{ m_state_data->window() }
    , m_quit{ false }
    , m_paused{ false }
    , m_exit_delay_time{ 0.f }
    , m_max_exit_delay_time{ 10.f }
{
    init_mouse_pos_text();
}

State::~State() = default;

void State::init_mouse_pos_text()
{
    m_mouse_pos_text.setCharacterSize(12);
    m_mouse_pos_text.setColor(sf::Color::White);
}

void State::update_mouse_pos_text()
{
    m_mouse_pos_text.setPosition(sf::Vector2f{ m_mouse_pos_view.x, m_mouse_pos_view.y - 25 });

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
    m_mouse_pos_grid = sf::Vector2i{ m_mouse_pos_view.x - static_cast<int>(m_mouse_pos_view.x) % m_state_data->grid_size()
                                   , m_mouse_pos_view.y - static_cast<int>(m_mouse_pos_view.y) % m_state_data->grid_size() };
}

void State::update_exit_delay_time(float dt)
{
    if (m_exit_delay_time <= m_max_exit_delay_time) {
        m_exit_delay_time += 50.f * dt;
    }
}

bool State::exit_delay_occurred()
{
    if (m_exit_delay_time > m_max_exit_delay_time) {
        m_exit_delay_time = 0;
        return true;
    }

    return false;
}

bool State::get_quit() const 
{
    return m_quit;
}

void State::end_state()
{
    m_quit = true;
}