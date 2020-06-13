#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "states/state.hpp"

class Button;

class SettingsState : public State
{
public:
    SettingsState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State *> * states);
    virtual ~SettingsState();

    void initFonts();
    void initButtons();
    void initBackground();
    void updateButtons(sf::Vector2f mousePos);
    void renderButtons(sf::RenderTarget & target);

    virtual void initKeybinds() override;
    virtual void updateInput() override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;

private:
    std::map<std::string, Button *> m_buttons;
    sf::RectangleShape m_background;
    sf::Font m_font;
};

#endif /* SETTINGS_STATE_H */