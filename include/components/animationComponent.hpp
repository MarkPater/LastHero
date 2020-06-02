#ifndef ANIMATION_COMPONENT_HPP
#define ANIMATION_COMPONENT_HPP

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Animation;

class AnimationComponent
{
public:
    AnimationComponent(sf::Sprite & sprite, sf::Texture & textureSheet);
    ~AnimationComponent();

    const bool & play(const std::string & action, const float & dt, const float & currentVelocity, const float & maxVelocity, const bool & priority = false);
    void addAnimation(const std::string key,
                        float animationTimer,
                        int start_frame_x, int start_frame_y,
                        int x_frames, int y_frames,
                        int widht, int height);

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
        bool m_isDone;
        int m_width;
        int m_height;
        sf::IntRect m_startRect;
        sf::IntRect m_currentRect;
        sf::IntRect m_endRect;

        const bool & play(const float & dt, const float & percentage);
        const bool & isDone();
        void reset();
    };

    void stopPreviosAnimation(const std::string & action);

    sf::Sprite & m_sprite;
    sf::Texture & m_textureSheet;

    Animation * m_lastAnimation;
    Animation * m_priorityAnimation;
    std::map<std::string, Animation *> m_animations;
};

#endif /* ANIMATION_COMPONENT_HPP */