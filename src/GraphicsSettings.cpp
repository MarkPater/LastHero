#include "GraphicsSettings.hpp"
#include "fstream"

GraphicsSettings::GraphicsSettings::GraphicsSettings()
    : m_video_modes{ sf::VideoMode::getFullscreenModes() }
    , m_window_title{ "LastHero" }
    , m_window_bounds{ sf::VideoMode::getDesktopMode() }
    , m_is_fullscreen{ false }
    , m_vertical_sync_enabled{ false }
    , m_framerate_limit{ 120 }
{

}

void GraphicsSettings::GraphicsSettings::load_from_file(const std::string & path)
{
    std::ifstream ifs{ path };

    if (ifs.is_open()) {
        std::getline(ifs, m_window_title);
        ifs >> m_window_bounds.width >> m_window_bounds.height;
        ifs >> m_is_fullscreen;
        ifs >> m_vertical_sync_enabled;
        ifs >> m_framerate_limit;
        ifs >> m_context_settings.antialiasingLevel;

        ifs.close();
    }
}

void GraphicsSettings::GraphicsSettings::save_to_file(const std::string & path)
{
    std::ofstream ofs{ path, std::ios::trunc };

    if (ofs.is_open()) {
        ofs << m_window_title << "\n";
        ofs << m_window_bounds.width << " " << m_window_bounds.height << "\n";
        ofs << m_is_fullscreen << "\n";
        ofs << m_vertical_sync_enabled << "\n";
        ofs << m_framerate_limit << "\n";
        ofs << m_context_settings.antialiasingLevel << "\n";

        ofs.close();
    }
}

std::vector<sf::VideoMode> GraphicsSettings::video_modes() const
{
    return m_video_modes;
}

std::string GraphicsSettings::window_title() const
{
    return m_window_title;
}

sf::VideoMode GraphicsSettings::window_bounds() const
{
    return m_window_bounds;
}

sf::ContextSettings GraphicsSettings::context_settings() const
{
    return m_context_settings;
}

bool GraphicsSettings::is_fullscreen() const
{
    return m_is_fullscreen;
}

bool GraphicsSettings::vertical_sync_enabled() const
{
    return m_vertical_sync_enabled;
}

int GraphicsSettings::framerate_limit() const
{
    return m_framerate_limit;
}

void GraphicsSettings::set_video_modes(const std::vector<sf::VideoMode> & video_modes)
{
    m_video_modes = video_modes;
}

void GraphicsSettings::set_window_title(const std::string & window_title)
{
    m_window_title = window_title;
}

void GraphicsSettings::set_window_bounds(const sf::VideoMode & video_mode)
{
    m_window_bounds = video_mode;
}

void GraphicsSettings::set_context_settings(const sf::ContextSettings & context_settings)
{
    m_context_settings = context_settings;
}

void GraphicsSettings::set_fullscreen(bool fullscreen)
{
    m_is_fullscreen = fullscreen;
}

void GraphicsSettings::set_vertical_sync_enabled(bool vertical_sync_enabled)
{
    m_vertical_sync_enabled = vertical_sync_enabled;
}

void GraphicsSettings::set_framerate_limit(int framerate_limit)
{
    m_framerate_limit = framerate_limit;
}