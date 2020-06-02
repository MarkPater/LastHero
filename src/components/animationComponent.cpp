#include <iostream>
#include "components/animationComponent.hpp"

AnimationComponent::Animation::Animation(sf::Sprite & sprite,
                                         sf::Texture & textureSheet,
                                         float animationTimer,
                                         int start_frame_x, int start_frame_y,
                                         int x_frames, int y_frames,
                                         int widht, int height)
    : m_sprite(sprite)
    , m_textureSheet(textureSheet)
    , m_animationTimer(animationTimer)
    , m_timer(0)
    , m_isDone(false)
    , m_width(widht)
    , m_height(height)
    , m_startRect(start_frame_x * widht, start_frame_y * height, widht, height)
    , m_currentRect(m_startRect)
    , m_endRect(x_frames * m_width, y_frames * m_height, widht, height)
{
    m_sprite.setTexture(textureSheet);
    m_sprite.setTextureRect(m_startRect);
}

AnimationComponent::Animation::~Animation()
{
}

const bool & AnimationComponent::Animation::play(const float & dt, const float & percentage)
{
    m_timer += (percentage > 0.5 ? percentage : 0.5) * 100.f * dt;
    m_isDone = false;

    if (m_timer >= m_animationTimer) {
        m_timer = 0;
        if (m_currentRect != m_endRect) {
            m_currentRect.left += m_width;
        }
        else {
            m_isDone = true;
            reset();
        }
    }
    m_sprite.setTextureRect(m_currentRect);
    
    return m_isDone;
}

const bool & AnimationComponent::Animation::isDone()
{
    return m_isDone;
}

void AnimationComponent::Animation::reset()
{
    m_currentRect = m_startRect;
}

AnimationComponent::AnimationComponent(sf::Sprite & sprite, sf::Texture & textureSheet)
    : m_sprite(sprite)
    , m_textureSheet(textureSheet)
    , m_lastAnimation(nullptr)
    , m_priorityAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
    for (const auto & animation : m_animations) {
        delete animation.second;
    }
}

void AnimationComponent::addAnimation(const std::string action,
                                      float animationTimer,
                                      int start_frame_x, int start_frame_y,
                                      int x_frames, int y_frames,
                                      int widht, int height)
{
    m_animations[action] = new AnimationComponent::Animation(m_sprite, m_textureSheet,
                                                             animationTimer,
                                                             start_frame_x, start_frame_y,
                                                             x_frames, y_frames,
                                                             widht, height);
}

const bool & AnimationComponent::play(const std::string & action, const float & dt, const float & currentVelocity, const float & maxVelocity, const bool & priority)
{
    stopPreviosAnimation(action);

    if (m_priorityAnimation) {
        const float percentage = (currentVelocity / maxVelocity) > 0.f ? (currentVelocity / maxVelocity) : -(currentVelocity / maxVelocity);
        if (m_animations[action]->play(dt, percentage)) {
            m_priorityAnimation = nullptr;
        }
    }
    else {
        if (priority) {
            m_priorityAnimation = m_animations[action];
        }
        const float percentage = (currentVelocity / maxVelocity) > 0.f ? (currentVelocity / maxVelocity) : -(currentVelocity / maxVelocity);
        m_animations[action]->play(dt, percentage);
    }

    return m_animations[action]->isDone();
}

void AnimationComponent::stopPreviosAnimation(const std::string & action)
{
    if (m_lastAnimation != m_animations[action]) {
        if (m_lastAnimation == nullptr) {
            m_lastAnimation = m_animations[action];
        }

        m_lastAnimation->reset();
        m_lastAnimation = m_animations[action];
    }
}