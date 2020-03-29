#ifndef ANIMATION_COMPONENT_HPP
#define ANIMATION_COMPONENT_HPP

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class AnimationComponent
{
private:
    class Animation
    {
    public:
        Animation(sf::Sprite & sprite, 
                  sf::Texture & textureSheet, 
                  float m_animationTimer,
                  int start_frame_x, int start_frame_y,
                  int x_frames, int y_frames,
                  int widht, int height);
        ~Animation();

        sf::Sprite & m_sprite;
        sf::Texture & m_textureSheet;
        float m_animationTimer;
        float m_timer;
        int m_width;
        int m_height;
        sf::IntRect m_startRect;
        sf::IntRect m_currentRect;
        sf::IntRect m_endRect;

        void play(const float & dt);
        void reset();
    };

    sf::Sprite & m_sprite;
    sf::Texture & m_textureSheet;

    Animation * m_lastAnimation;
    std::map<std::string, Animation *> m_animations;

public:
    AnimationComponent(sf::Sprite & sprite, sf::Texture & textureSheet);
    ~AnimationComponent();

    void play(const std::string key, const float & dt);
    void addAnimation(const std::string key,
                      float animationTimer,
                      int start_frame_x, int start_frame_y,
                      int x_frames, int y_frames,
                      int widht, int height);
};

#endif /* ANIMATION_COMPONENT_HPP */