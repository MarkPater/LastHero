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

    bool play(const std::string & action, float dt, float current_velocity, float max_velocity, const bool priority = false);
    void add_animation(const std::string & key,
                        float animation_timer,
                        int start_frame_x, int start_frame_y,
                        int x_frames, int y_frames,
                        int widht, int height);

private:
    class Animation
    {
    public:
        Animation(sf::Sprite & sprite, 
                  sf::Texture & texture_sheet, 
                  float m_animation_timer,
                  int start_frame_x, int start_frame_y,
                  int x_frames, int y_frames,
                  int widht, int height);
        ~Animation();

        sf::Sprite & m_sprite;
        sf::Texture & m_texture_sheet;
        float m_animation_timer;
        float m_timer;
        bool m_is_done;
        int m_width;
        int m_height;
        sf::IntRect m_start_rect;
        sf::IntRect m_current_rect;
        sf::IntRect m_end_rect;

        bool play(float dt, float percentage);
        bool is_done();
        void reset();
    };

    void stop_previos_animation(const std::string & action);

    sf::Sprite & m_sprite;
    sf::Texture & m_texture_sheet;

    Animation * m_last_animation;
    Animation * m_priority_animation;
    std::map<std::string, Animation *> m_animations;
};

#endif /* ANIMATION_COMPONENT_HPP */