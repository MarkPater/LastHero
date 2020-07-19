#include "GUI/Gui.hpp"
#include "GraphicsSettings.hpp"

#include <cassert>
#include <iostream>

////////////////////////////   gui::Button   ////////////////////////////
gui::Button::Button(unsigned x,
                    unsigned y, 
                    unsigned width,
                    unsigned height,
                    sf::Font & font,
                    const std::string & text,
                    unsigned character_size)
    : m_button_state(static_cast<unsigned short>(ButtonState::BTN_IDLE))
    , m_font(font)
    , m_check_only_text(false)
    , m_id(0)
{
    set_idle_colors();
    set_hover_colors();
    set_active_colors();

    m_button_shape.setPosition(x, y);
    m_button_shape.setSize(sf::Vector2f(width, height));
    m_button_shape.setFillColor(m_idle_button_color);
    m_button_shape.setOutlineColor(m_idle_outline_button_color);
    m_button_shape.setOutlineThickness(2);

    sf::Text for_center;
    for_center.setString(text[0]);
    for_center.setCharacterSize(character_size);
    for_center.setFont(font);

    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(character_size);
    m_text.setStyle(sf::Text::Style::Italic);
    m_text.setOutlineThickness(2);
    m_text.setOutlineColor(m_idle_outline_text_color);
    m_text.setPosition(
        m_button_shape.getPosition().x + width / 2.f - m_text.getGlobalBounds().width / 2.f,
        m_button_shape.getPosition().y + height / 2.f - for_center.getGlobalBounds().height / 1.20f
    );
}

gui::Button::~Button()
{

}

std::string gui::Button::text() const
{
    return m_text.getString().toAnsiString();
}

void gui::Button::set_text(const std::string & text)
{
    m_text.setString(text);
}

int gui::Button::id() const
{
    return m_id;
}

void gui::Button::set_id(unsigned short id)
{
    m_id = id;
}

void gui::Button::set_check_only_text(bool check_only_text)
{
    m_check_only_text = check_only_text;
}

void gui::Button::set_idle_colors(sf::Color idle_button_color,
                                  sf::Color idle_text_color,
                                  sf::Color idle_outline_button_color,
                                  sf::Color idle_outline_text_color)
{
    m_idle_button_color = idle_button_color;
    m_idle_text_color = idle_text_color;
    m_idle_outline_button_color = idle_outline_button_color;
    m_idle_outline_text_color = idle_outline_text_color;
}

void gui::Button::set_hover_colors(sf::Color hover_button_color,
                                   sf::Color hover_text_color,
                                   sf::Color hover_outline_button_color,
                                   sf::Color hover_outline_text_color)
{
    m_hover_button_color = hover_button_color;
    m_hover_text_color = hover_text_color;
    m_hover_outline_button_color = hover_outline_text_color;
    m_hover_outline_text_color = hover_outline_text_color;
}

void gui::Button::set_active_colors(sf::Color active_button_color,
                                   sf::Color active_text_color,
                                   sf::Color active_outline_button_color,
                                   sf::Color active_outline_text_color)
{
    m_active_button_color = active_button_color;
    m_active_text_color = active_text_color;
    m_active_outline_button_color = active_outline_text_color;
    m_active_outline_text_color = active_outline_text_color;
}

void gui::Button::set_button_colors(sf::Color idle_button_color,
                                    sf::Color hover_button_color, 
                                    sf::Color active_button_color)
{
    m_idle_button_color = idle_button_color;
    m_hover_button_color = hover_button_color;
    m_active_button_color = active_button_color;
}

void gui::Button::set_text_colors(sf::Color idle_text_color,
                                  sf::Color hover_text_color, 
                                  sf::Color active_text_color)
{
    m_idle_text_color = idle_text_color;
    m_hover_text_color = hover_text_color;
    m_active_text_color = active_text_color;
}

void gui::Button::set_outline_button_colors(sf::Color idle_outline_button_color,
                                            sf::Color hover_outline_button_color,
                                            sf::Color active_outline_button_color)
{
    m_idle_outline_button_color = idle_outline_button_color;
    m_hover_outline_button_color = hover_outline_button_color;
    m_active_outline_button_color = active_outline_button_color;
}

void gui::Button::set_outline_text_colors(sf::Color idle_outline_text_color,
                                          sf::Color hover_outline_text_color,
                                          sf::Color active_outline_text_color)
{
    m_idle_outline_text_color = idle_outline_text_color;
    m_hover_outline_text_color = hover_outline_text_color;
    m_active_outline_text_color = active_outline_text_color;
}

bool gui::Button::is_pressed() const
{
    return m_button_state == static_cast<unsigned short>(ButtonState::BTN_ACTIVE) ? true : false;
}

void gui::Button::update(sf::Vector2f mouse_pos)
{
    m_button_state = static_cast<unsigned short>(ButtonState::BTN_IDLE);

    if (m_check_only_text) {
        if (m_text.getGlobalBounds().contains(mouse_pos)) {
            m_button_state = static_cast<unsigned short>(ButtonState::BTN_HOVER);
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                m_button_state = static_cast<unsigned short>(ButtonState::BTN_ACTIVE);
            }
        }
    }
    else {
        if (m_button_shape.getGlobalBounds().contains(mouse_pos)) {
            m_button_state = static_cast<unsigned short>(ButtonState::BTN_HOVER);
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                m_button_state = static_cast<unsigned short>(ButtonState::BTN_ACTIVE);
            }
        }
    }

    switch (m_button_state) {
        case static_cast<unsigned short>(ButtonState::BTN_IDLE): {
            m_button_shape.setFillColor(m_idle_button_color);
            m_button_shape.setOutlineColor(m_idle_outline_button_color);
            m_text.setFillColor(m_idle_text_color);
            m_text.setOutlineColor(m_idle_outline_text_color);
            break;
        }
        case static_cast<unsigned short>(ButtonState::BTN_HOVER): {
            m_button_shape.setFillColor(m_hover_button_color);
            m_button_shape.setOutlineColor(m_hover_outline_button_color);
            m_text.setFillColor(m_hover_text_color);
            m_text.setOutlineColor(m_hover_outline_text_color);
            break;
        }
        case static_cast<unsigned short>(ButtonState::BTN_ACTIVE): {
            m_button_shape.setFillColor(m_active_button_color);
            m_button_shape.setOutlineColor(m_active_outline_button_color);
            m_text.setFillColor(m_active_text_color);
            m_text.setOutlineColor(m_active_outline_text_color);
            break;
        }
        default: {
            assert(false && "Button::update::undefined_button_state");
            exit(EXIT_FAILURE);
        }
    }
}

void gui::Button::render(sf::RenderTarget & target)
{
    target.draw(m_button_shape);
    target.draw(m_text);
}

////////////////////////////   gui::ComboBox   ////////////////////////////
gui::ComboBox::ComboBox(sf::Font & font, unsigned x, unsigned y, unsigned width, unsigned height)
    : m_font(font)
    , m_active_element(nullptr)
    , m_show_elements(false)
    , m_delay_time(0.f)
    , m_max_delay_time(10.f)
    , m_x(x)
    , m_y(y)
    , m_width(width)
    , m_height(height)
    , m_last_id(0)
{
}

gui::ComboBox::~ComboBox()
{
    clear();
}

void gui::ComboBox::clear()
{
    for (int i = m_elements.size() - 1; i >= 0; --i) {
        delete m_elements[i];
        m_elements.pop_back();
    }
}

int gui::ComboBox::count() const
{
    return m_elements.size();
}

void gui::ComboBox::add_item(const std::string & text, unsigned character_size)
{
    if (!m_active_element) {
        m_active_element = new Button(m_x, m_y + (m_elements.size() * m_height), m_width, m_height, m_font, text, character_size);
        m_active_element->set_outline_button_colors(sf::Color(80, 225, 170, 220), sf::Color(80, 115, 220, 220), sf::Color(120, 175, 120, 220));
        m_elements.push_back(m_active_element);
        m_elements[0]->set_id(m_last_id);
    }

    m_elements.push_back(new Button(m_x, m_y + (m_elements.size() * m_height), m_width, m_height, m_font, text, character_size));
    m_elements[m_elements.size() - 1]->set_id(m_last_id++);
}

void gui::ComboBox::add_items(const std::string text[], unsigned size, unsigned character_size)
{
    if (!m_active_element && size > 0) {
        m_active_element = new Button(m_x, m_y + (m_elements.size() * m_height), m_width, m_height, m_font, text[0], character_size);
        m_active_element->set_outline_button_colors(sf::Color(80, 225, 170, 220), sf::Color(80, 115, 220, 220), sf::Color(120, 175, 120, 220));
        m_elements.push_back(m_active_element);
        m_elements[0]->set_id(m_last_id);
    }
    
    for (int i = 0; i < size; ++i) {
        m_elements.push_back(new Button(m_x, m_y + (m_elements.size() * m_height), m_width, m_height, m_font, text[i], character_size));
        m_elements[m_elements.size() - 1]->set_id(m_last_id++);
    }
}

int gui::ComboBox::current_index() const
{
    return m_active_element->id();
}

void gui::ComboBox::set_current_index(unsigned index)
{
    m_active_element = m_elements[index];
}

void gui::ComboBox::show_elements()
{
    m_show_elements = true;
}

void gui::ComboBox::hide_elements()
{
    m_show_elements = false;
}

void gui::ComboBox::update_delay_time(float dt)
{
    if (m_delay_time <= m_max_delay_time) {
        m_delay_time += 50 * dt;
    }
}

bool gui::ComboBox::delay_occured()
{
    if (m_delay_time > m_max_delay_time) {
        m_delay_time = 0;
        return true;
    }
    return false;
}

void gui::ComboBox::update_input(sf::Vector2f mouse_pos, Button * element)
{
    if (element->is_pressed() && delay_occured()) {
        if (m_show_elements) {
            m_active_element->set_text(element->text());
            m_active_element->set_id(element->id());
            hide_elements();
        }
        else {
            show_elements();
        }
    }
}

void gui::ComboBox::update(float dt, sf::Vector2f mouse_pos)
{
    update_delay_time(dt);
    m_active_element->update(mouse_pos);
    update_input(mouse_pos, m_active_element);

    if (m_show_elements) {
        for (const auto & element : m_elements) {
            element->update(mouse_pos);
            update_input(mouse_pos, element);
        }
    }
}

void gui::ComboBox::render(sf::RenderTarget & target)
{
    m_active_element->render(target);

    if (m_show_elements) {
        for (const auto & element : m_elements) {
            element->render(target);
        }
    }
}

////////////////////////////   gui::TextureSelector   ////////////////////////////
gui::TextureSelector::TextureSelector(int x, int y, int width, int height, int grid_size, const sf::Texture * texture_sheet, sf::Font & font)
    : m_bounds{ sf::Vector2f{ width, height } }
    , m_selector_rect{ sf::Vector2f{ grid_size, grid_size } }
    , m_ts_button{ std::unique_ptr<gui::Button>{ new gui::Button{ x, y, 65, 65, font, "TS", 35 } } }
    , m_grid_size{ grid_size }
    , m_is_visible{ false }
    , m_is_active{ false }
    , m_delay_time{ -10 }
    , m_max_delay_time{ 10 }
    , m_x_offset{ 85 }
{
    m_bounds.setPosition(x + m_x_offset, y);
    m_bounds.setFillColor(sf::Color{ 50, 50, 50, 100 });
    m_bounds.setOutlineColor(sf::Color{ 255, 255, 255, 200 });
    m_bounds.setOutlineThickness(1);

    m_texture_sheet.setPosition(x + m_x_offset, y);
    m_texture_sheet.setTexture(*texture_sheet);

    m_selector_rect.setPosition(x + m_x_offset, y);
    m_selector_rect.setFillColor(sf::Color::Transparent);
    m_selector_rect.setOutlineColor(sf::Color::Red);
    m_selector_rect.setOutlineThickness(1);

    m_ts_button->set_outline_button_colors(sf::Color{ 255, 255, 255, 135 }, sf::Color{ 255, 255, 255, 150 }, sf::Color{ 255, 255, 255, 255 });
    m_ts_button->set_button_colors(sf::Color{ 50, 50, 50, 175 }, sf::Color{ 80, 80, 80, 195 }, sf::Color{ 110, 110, 110, 215 });
}

bool gui::TextureSelector::is_visible() const
{
    return m_is_visible;
}

bool gui::TextureSelector::is_active() const
{
    return m_is_active;
}

sf::IntRect gui::TextureSelector::selected_tile_rect() const
{
    return sf::IntRect{ m_selector_rect.getPosition().x - m_bounds.getPosition().x
                      , m_selector_rect.getPosition().y - m_bounds.getPosition().y
                      , m_grid_size, m_grid_size };
}

void gui::TextureSelector::update_delay_time(float dt)
{
    if (m_delay_time <= m_max_delay_time) {
        m_delay_time += 50 * dt;
    }
}

bool gui::TextureSelector::delay_occured()
{
    if (m_delay_time > m_max_delay_time) {
        m_delay_time = 0;
        return true;
    }
    return false;
}

sf::Vector2f gui::TextureSelector::mouse_pos_grid(sf::Vector2i mouse_pos_window) const
{
    int row    = (mouse_pos_window.x - m_bounds.getPosition().x) / m_grid_size;
    int column = (mouse_pos_window.y - m_bounds.getPosition().y) / m_grid_size;

    return sf::Vector2f{ m_bounds.getPosition().x + row * m_grid_size
                       , m_bounds.getPosition().y + column * m_grid_size };

}

void gui::TextureSelector::update(float dt, sf::Vector2i mouse_pos_window)
{
    m_ts_button->update(static_cast<sf::Vector2f>(mouse_pos_window));
    update_delay_time(dt);

    if (m_ts_button->is_pressed() && delay_occured()) {
        m_is_visible = !m_is_visible;
    }

    if (m_is_visible) {
        m_is_active = m_bounds.getGlobalBounds().contains(mouse_pos_window.x, mouse_pos_window.y);

        if (m_is_active) {
            m_selector_rect.setPosition(mouse_pos_grid(mouse_pos_window));
        }
    }
}

void gui::TextureSelector::render(sf::RenderTarget & render_target)
{
    m_ts_button->render(render_target);

    if (m_is_visible) {
        render_target.draw(m_bounds);
        render_target.draw(m_texture_sheet);
        render_target.draw(m_selector_rect);
    }
}

////////////////////////////   gui::Sidebar   ////////////////////////////
gui::Sidebar::Sidebar(sf::VideoMode window_bounds, gui::WindowSide window_side, int thickness)
    : m_is_visible{ true }
    , m_is_active{ false }
{
    switch (window_side) {
        case gui::WindowSide::Left: {
            m_body.setPosition(0, 0);
            m_body.setSize(sf::Vector2f{ thickness, window_bounds.height });
            break;
        }
        case gui::WindowSide::Right: {
            m_body.setPosition(window_bounds.width - thickness, 0);
            m_body.setSize(sf::Vector2f{ thickness, window_bounds.height });
            break;
        }
        case gui::WindowSide::Up: {
            m_body.setPosition(0, 0);
            m_body.setSize(sf::Vector2f{ window_bounds.width, thickness });
            break;
        }
        case gui::WindowSide::Down: {
            m_body.setPosition(0, window_bounds.height - thickness);
            m_body.setSize(sf::Vector2f{ window_bounds.width, thickness });
            break;
        }
        default: {
            assert(false && "Sidebar::Sidebar::undefined_side_state");
            exit(EXIT_FAILURE);
        }
    }

    m_body.setOutlineThickness(1);
    m_body.setOutlineColor(sf::Color{ 200, 200, 200, 180 });
    m_body.setFillColor(sf::Color{ 50, 50, 50, 100 });
}

bool gui::Sidebar::is_visible() const
{
    return m_is_visible;
}

bool gui::Sidebar::is_active() const
{
    return m_is_active;
}

void gui::Sidebar::update(sf::Vector2f mouse_pos)
{
    m_is_active = m_body.getGlobalBounds().contains(mouse_pos);
}

void gui::Sidebar::render(sf::RenderTarget & render_target)
{
    render_target.draw(m_body);
}