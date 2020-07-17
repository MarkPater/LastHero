#ifndef EDITOR_STATE_HPP
#define EDITOR_STATE_HPP

#include "states/State.hpp"
#include "GUI/Gui.hpp"
#include "map/TileMap.hpp"

class PauseMenu;
class StateData;

class EditorState : public State {
public:
    EditorState(std::shared_ptr<StateData> state_data);
    virtual ~EditorState();

    void init_font();
    void init_gui();
    void init_buttons();
    void init_pause_menu();
    bool tile_delay_occurred();
    void update_editor_input();
    void update_pause_menu_input();
    void update_buttons(sf::Vector2f mouse_pos);
    void update_gui();
    void update_tile_delay_time(float dt);
    void render_buttons(sf::RenderTarget & target);
    void render_gui(sf::RenderTarget & target);

    virtual void init_mouse_pos_text() override;
    virtual void init_keybinds() override;
    virtual void update_input() override;
    virtual void update_mouse_pos_text() override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

protected:
    std::unique_ptr<TileMap> m_tile_map;
    std::unique_ptr<PauseMenu> m_pause_menu;
    std::map<std::string, std::unique_ptr<gui::Button>> m_buttons;

    sf::Font m_font;
    sf::Text m_rect_pos_text;
    sf::RectangleShape m_selector_rect;
    sf::IntRect m_tile_rect;

    float m_tile_delay_time;
    const float m_tile_max_delay_time;
};

#endif /* EDITOR_STATE_HPP */