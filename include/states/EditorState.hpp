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
    void init_buttons();
    void init_pause_menu();
    void update_input();
    void update_pause_menu_input();
    void update_buttons(sf::Vector2f mouse_pos);
    void render_buttons(sf::RenderTarget & target);

    virtual void init_mouse_pos_text() override;
    virtual void init_keybinds() override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

protected:
    sf::Font m_font;
    
    std::map<std::string, gui::Button *> m_buttons;
    std::unique_ptr<PauseMenu> m_pause_menu;
    std::unique_ptr<TileMap> m_tile_map;
};

#endif /* EDITOR_STATE_HPP */