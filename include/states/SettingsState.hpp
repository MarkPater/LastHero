#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "states/State.hpp"
#include "GUI/Gui.hpp"

#include <memory>

class GraphicsSettings;

class SettingsState : public State
{
public:
    SettingsState(sf::RenderWindow * window, std::shared_ptr<GraphicsSettings> gfx_settings, std::map<std::string, int> * supported_keys, std::stack<State *> * states);
    virtual ~SettingsState();

    void init_gui();
    void init_fonts();
    void init_settings();
    void init_background();
    void update_gui(float dt, sf::Vector2f mouse_pos);
    void render_gui(sf::RenderTarget & target);

    virtual void init_mouse_pos_text() override;
    virtual void init_keybinds() override;
    virtual void update_input() override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

private:
    std::vector<std::string> from_video_modes_to_strings() const;

    std::map<std::string, gui::ComboBox *> m_combo_boxes;
    std::map<std::string, gui::Button *> m_buttons;
    std::vector<sf::VideoMode> m_video_modes;
    std::shared_ptr<GraphicsSettings> m_gfx_settings;

    sf::RectangleShape m_background;
    sf::Text m_settings_text;
    sf::Font m_font;
};

#endif /* SETTINGS_STATE_H */