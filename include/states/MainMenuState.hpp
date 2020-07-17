#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "states/State.hpp"
#include "GUI/Gui.hpp"

class StateData;

class MainMenuState : public State {
public:
    MainMenuState(std::shared_ptr<StateData> state_data);
    virtual ~MainMenuState();

    void init_fonts();
    void init_gui();
    void init_background();
    void update_buttons(sf::Vector2f mouse_pos);
    void render_buttons(sf::RenderTarget & target);

    virtual void init_mouse_pos_text() override;
    virtual void update_input() override;
    virtual void init_keybinds() override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

protected:
    std::map<std::string, std::unique_ptr<gui::Button>> m_buttons;

    sf::RectangleShape m_background;
    sf::Texture m_background_texture;
    sf::Font m_font;
};

#endif /* MAIN_MENU_STATE_HPP */