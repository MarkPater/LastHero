#ifndef GRAPHICS_SETTINGS_HPP
#define GRAPHICS_SETTINGS_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

struct GraphicsSettings
{
    GraphicsSettings();

    void load_from_file(const std::string & path);
    void save_to_file(const std::string & path);

    // TODO: make it section private and take these settings via getters
    std::string m_window_title;
    sf::VideoMode m_window_bounds;
    std::vector<sf::VideoMode> m_video_modes;
    bool m_is_fullscreen;
    bool m_vertical_sync_enabled;
    int m_framerate_limit;
    sf::ContextSettings m_context_settings;
};

#endif /* GRAPHICS_SETTINGS_HPP */