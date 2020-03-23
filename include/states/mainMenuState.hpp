#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "states/gameState.hpp"
#include "button.hpp"

class MainMenuState : public State {
public:
    MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys);
    virtual ~MainMenuState();

    void initFont();

    virtual void initKeybinds() override;
    virtual void updateKeybinds(const float & dt) override;
    virtual void update(const float & dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;
    virtual void endState() override;

protected:
    sf::RectangleShape m_mainPreview;
    sf::Font m_font;

    Button * m_gameStateButton;
};

#endif /* MAIN_MENU_STATE_HPP */