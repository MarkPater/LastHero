#ifndef EDITOR_STATE_HPP
#define EDITOR_STATE_HPP

#include "states/state.hpp"
#include "GUI/gui.hpp"

class EditorState : public State {
public:
    EditorState(sf::RenderWindow * window, std::map<std::string, int> * supported_keys, std::stack<State *> * states);
    virtual ~EditorState();

    void init_font();
    void init_buttons();
    void update_input();
    void update_buttons(sf::Vector2f mouse_pos);
    void render_buttons(sf::RenderTarget & target);

    virtual void init_mouse_pos_text() override;
    virtual void init_keybinds() override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

protected:
    sf::Font m_font;
    std::map<std::string, gui::Button *> m_buttons;
};

#endif /* EDITOR_STATE_HPP */