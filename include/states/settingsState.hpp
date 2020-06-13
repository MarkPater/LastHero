#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "states/state.hpp"
#include "GUI/gui.hpp"

class SettingsState : public State
{
public:
    SettingsState(sf::RenderWindow * window, std::map<std::string, int> * supported_keys, std::stack<State *> * states);
    virtual ~SettingsState();

    void init_gui();
    void init_fonts();
    void init_background();
    void update_gui(float dt, sf::Vector2f mouse_pos);
    void render_gui(sf::RenderTarget & target);

    virtual void initKeybinds() override;
    virtual void updateInput() override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

private:
    std::map<std::string, gui::ComboBox * > m_combo_boxes;
    std::map<std::string, gui::Button *> m_buttons;
    sf::RectangleShape m_background;
    sf::Font m_font;
};

#endif /* SETTINGS_STATE_H */