#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <string>

namespace gui 
{
    /// Simple button
    class Button
    {
    public:
        Button(unsigned x,
               unsigned y, 
               unsigned width,
               unsigned height,
               sf::Font & font,
               const std::string & text,
               unsigned character_size = 45);
        ~Button();

        std::string text() const;
        void set_text(const std::string & text);
        int id() const;
        void set_id(unsigned short id);
        void set_check_only_text(bool check_only_text);
        void set_idle_colors(sf::Color idle_button_color = sf::Color(35, 35, 35, 180),
                             sf::Color idle_text_color = sf::Color(255, 255, 255, 255),
                             sf::Color idle_outline_button_color = sf::Color::Transparent,
                             sf::Color idle_outline_text_color = sf::Color::Transparent);
        void set_hover_colors(sf::Color hover_button_color = sf::Color(80, 80, 80, 180),
                              sf::Color hover_text_color = sf::Color(115, 115, 255, 240),
                              sf::Color hover_outline_button_color = sf::Color::Transparent,
                              sf::Color hover_outline_text_color = sf::Color::Transparent);
        void set_active_colors(sf::Color active_button_color = sf::Color(195, 195, 195, 100),
                               sf::Color active_text_color = sf::Color(235, 255, 235, 250),
                               sf::Color active_outline_button_color = sf::Color::Transparent,
                               sf::Color active_outline_text_color = sf::Color::Transparent);
        void set_button_colors(sf::Color idle_button_color = sf::Color::Transparent,
                               sf::Color hover_button_color = sf::Color::Transparent,
                               sf::Color active_button_color = sf::Color::Transparent);
        void set_text_colors(sf::Color idle_text_color = sf::Color(215, 215, 215, 235),
                             sf::Color hover_text_color = sf::Color(175, 215, 255, 210),
                             sf::Color active_text_color = sf::Color(235, 255, 235, 250));
        void set_outline_button_colors(sf::Color idle_outline_button_color = sf::Color::Transparent,
                                       sf::Color hover_outline_button_color = sf::Color::Transparent,
                                       sf::Color active_outline_button_color = sf::Color::Transparent);
        void set_outline_text_colors(sf::Color idle_outline_text_color = sf::Color::Transparent,
                                     sf::Color hover_outline_text_color = sf::Color::Transparent,
                                     sf::Color active_outline_text_color = sf::Color::Transparent);

        bool is_pressed() const;
        void update(sf::Vector2f mouse_pos);
        void render(sf::RenderTarget & target);

    private:
        sf::RectangleShape m_button_shape;
        sf::Font & m_font;
        sf::Text m_text;
        sf::Color m_idle_text_color;
        sf::Color m_hover_text_color;
        sf::Color m_active_text_color;
        sf::Color m_idle_button_color;
        sf::Color m_hover_button_color;
        sf::Color m_active_button_color;
        sf::Color m_idle_outline_text_color;
        sf::Color m_hover_outline_text_color;
        sf::Color m_active_outline_text_color;
        sf::Color m_idle_outline_button_color;
        sf::Color m_hover_outline_button_color;
        sf::Color m_active_outline_button_color;

        unsigned short m_button_state;
        unsigned short m_id;
        bool m_check_only_text;

        enum class ButtonState {
            BTN_IDLE = 0,
            BTN_HOVER,
            BTN_ACTIVE
        };
    };
    
    /// Drop down list
    class ComboBox
    {
    public:
        ComboBox(sf::Font & font,
                 unsigned x,
                 unsigned y,
                 unsigned width,
                 unsigned height);
        ~ComboBox();

        void clear();
        int count() const;

        void add_item(const std::string & text,
                     unsigned character_size = 35);
        void add_items(const std::string text[],
                      unsigned size, unsigned character_size = 35);
        int current_index() const;
        void set_current_index(unsigned index);
        void update_input(sf::Vector2f mouse_pos, Button * element);
        void update(float dt, sf::Vector2f mouse_pos);
        void render(sf::RenderTarget & target);

    private:
        void show_elements();
        void hide_elements();
        void update_delay_time(float dt);
        bool delay_occured();

        std::vector<Button *> m_elements;
        sf::Font & m_font;
        Button * m_active_element;
        bool m_show_elements;
        float m_delay_time;
        const float m_max_delay_time;
        const unsigned m_x;
        const unsigned m_y;
        const unsigned m_width;
        const unsigned m_height;
        unsigned short m_last_id;
    };
}

#endif /* GUI_HPP */