#ifndef EDITOR_STATE_HPP
#define EDITOR_STATE_HPP

#include "states/state.hpp"
#include "button.hpp"

class EditorState : public State {
public:
    EditorState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states);
    virtual ~EditorState();

    void initFont();
    void initButtons();
    void initMousePos();
    void updateInput();
    void updateMousePosText();
    void updateButtons(sf::Vector2f mousePos);
    void renderButtons(sf::RenderTarget * target = nullptr);

    virtual void initKeybinds() override;
    virtual void update(const float & dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

protected:
    sf::Text m_mousePosText;
    sf::Font m_font;

    std::map<std::string, Button *> m_buttons;
};

#endif /* EDITOR_STATE_HPP */