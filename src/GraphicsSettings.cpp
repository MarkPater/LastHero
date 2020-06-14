#include "GraphicsSettings.hpp"
#include "fstream"

GraphicsSettings::GraphicsSettings::GraphicsSettings()
    : m_window_title{ "LastHero" }
    , m_window_bounds{ sf::VideoMode::getDesktopMode() }
    , m_video_modes{ sf::VideoMode::getFullscreenModes() }
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
    }
    ifs.close();
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
    }
    ofs.close();
}