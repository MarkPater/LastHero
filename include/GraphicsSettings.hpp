#ifndef GRAPHICS_SETTINGS_HPP
#define GRAPHICS_SETTINGS_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <string>
#include <vector>

struct GraphicsSettings
{
    GraphicsSettings();

    void load_from_file(const std::string & path);
    void save_to_file(const std::string & path);

    std::vector<sf::VideoMode> video_modes() const;
    std::string window_title() const;
    sf::VideoMode window_bounds() const;
    sf::ContextSettings context_settings() const;
    bool is_fullscreen() const;
    bool vertical_sync_enabled() const;
    int framerate_limit() const;

    void set_video_modes(const std::vector<sf::VideoMode> & video_modes);
    void set_window_title(const std::string & window_title);
    void set_window_bounds(const sf::VideoMode & video_mode);
    void set_context_settings(const sf::ContextSettings & context_settings);
    void set_fullscreen(bool fullscreen);
    void set_vertical_sync_enabled(bool vertical_sync_enabled);
    void set_framerate_limit(int framerate_limit);

private:
    std::vector<sf::VideoMode> m_video_modes;
    std::string m_window_title;

    sf::VideoMode m_window_bounds;
    sf::ContextSettings m_context_settings;

    bool m_is_fullscreen;
    bool m_vertical_sync_enabled;
    int m_framerate_limit;
};

#endif /* GRAPHICS_SETTINGS_HPP */