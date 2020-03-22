#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <states/state.hpp>

class GameState : public State 
{
public:
    GameState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys);
    ~GameState();

    virtual void initKeybinds() override;

    virtual void updateKeybinds(const float & dt) override;
    virtual void update(const float & dt) override;
    virtual void render(sf::RenderTarget * target = nullptr) override;
    virtual void endState() override;

protected:
    Entity player;
};

#endif /* GAME_STATE_HPP */