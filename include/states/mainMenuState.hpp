#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "states/state.hpp"
#include "GUI/gui.hpp"

class MainMenuState : public State {
public:
    MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supported_keys, std::stack<State *> * states);
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
    sf::RectangleShape m_background;
    sf::Texture m_background_texture;
    sf::Font m_font;

    std::map<std::string, gui::Button *> m_buttons;
};

#endif /* MAIN_MENU_STATE_HPP */