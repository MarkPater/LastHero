#include "components/animationComponent.hpp"

AnimationComponent::Animation::Animation(sf::Sprite & sprite,
                                         sf::Texture & textureSheet,
                                         float animationTimer,
                                         int start_frame_x, int start_frame_y,
                                         int x_frames, int y_frames,
                                         int widht, int height) :
    m_sprite(sprite),
    m_textureSheet(textureSheet),
    m_animationTimer(animationTimer),
    m_timer(0),
    m_width(widht),
    m_height(height),
    m_startRect(start_frame_x * widht, start_frame_y * height, widht, height),
    m_currentRect(m_startRect),
    m_endRect(x_frames * m_width, y_frames * m_height, widht, height)
{
    m_sprite.setTexture(textureSheet);
    m_sprite.setTextureRect(m_startRect);
}

AnimationComponent::Animation::~Animation()
{
}

void AnimationComponent::Animation::play(const float & dt)
{
    m_timer += 1000.f * dt;

    if (m_timer >= m_animationTimer) {
        m_timer = 0;
        if (m_currentRect != m_endRect) {
            m_currentRect.left += m_width;
        }
        else {
            reset();
        }
    }

    m_sprite.setTextureRect(m_currentRect);
}

void AnimationComponent::Animation::reset()
{
    m_currentRect = m_startRect;
    m_timer = 0.f;
}

AnimationComponent::AnimationComponent(sf::Sprite & sprite, sf::Texture & textureSheet) :
    m_sprite(sprite),
    m_textureSheet(textureSheet),
    m_lastAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
    for (const auto & animation : m_animations) {
        delete animation.second;
    }
}

void AnimationComponent::addAnimation(const std::string key,
                                      float animationTimer,
                                      int start_frame_x, int start_frame_y,
                                      int x_frames, int y_frames,
                                      int widht, int height)
{
    m_animations[key] = new Animation(m_sprite, m_textureSheet,
                                      animationTimer,
                                      start_frame_x, start_frame_y,
                                      x_frames, y_frames,
                                      widht, height);
}

void AnimationComponent::play(const std::string key, const float & dt)
{
    if (m_lastAnimation != m_animations[key]) {
        if (m_lastAnimation == nullptr) {
            m_lastAnimation = m_animations[key];
        }

        m_lastAnimation->reset();
        m_lastAnimation = m_animations[key];
    }

    m_animations[key]->play(dt);
}