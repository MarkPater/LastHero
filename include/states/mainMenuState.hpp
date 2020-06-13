#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "states/state.hpp"

class Button;

class MainMenuState : public State {
public:
    MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states);
    virtual ~MainMenuState();

    void initFonts();
    void initButtons();
    void initMousePos();
    void initBackground();
    void updateMousePosText();
    void updateButtons(sf::Vector2f mousePos);
    void renderButtons(sf::RenderTarget & target);

    virtual void updateInput() override;
    virtual void initKeybinds() override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

protected:
    sf::RectangleShape m_background;
    sf::Texture m_backgroundTexture;
    sf::Text m_mousePosText;
    sf::Font m_font;

    std::map<std::string, Button *> m_buttons;
};

#endif /* MAIN_MENU_STATE_HPP */