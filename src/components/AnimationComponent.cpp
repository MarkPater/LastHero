#include "components/AnimationComponent.hpp"

AnimationComponent::Animation::Animation(sf::Sprite & sprite,
                                         sf::Texture & texture_sheet,
                                         float animation_timer,
                                         int start_frame_x, int start_frame_y,
                                         int x_frames, int y_frames,
                                         int widht, int height)
    : m_sprite(sprite)
    , m_texture_sheet(texture_sheet)
    , m_animation_timer(animation_timer)
    , m_timer(0)
    , m_is_done(false)
    , m_width(widht)
    , m_height(height)
    , m_start_rect(start_frame_x * widht, start_frame_y * height, widht, height)
    , m_current_rect(m_start_rect)
    , m_end_rect(x_frames * m_width, y_frames * m_height, widht, height)
{
    m_sprite.setTexture(texture_sheet);
    m_sprite.setTextureRect(m_start_rect);
}

AnimationComponent::Animation::~Animation()
{
}

bool AnimationComponent::Animation::play(float dt, float percentage)
{
    m_timer += (percentage > 0.5 ? percentage : 0.5) * 100.f * dt;
    m_is_done = false;

    if (m_timer >= m_animation_timer) {
        m_timer = 0;
        if (m_current_rect != m_end_rect) {
            m_current_rect.left += m_width;
        }
        else {
            m_is_done = true;
            reset();
        }
    }
    m_sprite.setTextureRect(m_current_rect);
    
    return m_is_done;
}

bool AnimationComponent::Animation::is_done()
{
    return m_is_done;
}

void AnimationComponent::Animation::reset()
{
    m_current_rect = m_start_rect;
}

AnimationComponent::AnimationComponent(sf::Sprite & sprite, sf::Texture & texture_sheet)
    : m_sprite(sprite)
    , m_texture_sheet(texture_sheet)
    , m_last_animation(nullptr)
    , m_priority_animation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
    for (const auto & animation : m_animations) {
        delete animation.second;
    }
}

void AnimationComponent::add_animation(const std::string & action,
                                      float animation_timer,
                                      int start_frame_x, int start_frame_y,
                                      int x_frames, int y_frames,
                                      int widht, int height)
{
    m_animations[action] = new AnimationComponent::Animation(m_sprite, m_texture_sheet,
                                                             animation_timer,
                                                             start_frame_x, start_frame_y,
                                                             x_frames, y_frames,
                                                             widht, height);
}

bool AnimationComponent::play(const std::string & action, float dt, float current_velocity, float max_velocity, const bool priority)
{
    stop_previos_animation(action);

    if (m_priority_animation) {
        const float percentage = (current_velocity / max_velocity) > 0.f ? (current_velocity / max_velocity) : -(current_velocity / max_velocity);
        if (m_animations[action]->play(dt, percentage)) {
            m_priority_animation = nullptr;
        }
    }
    else {
        if (priority) {
            m_priority_animation = m_animations[action];
        }
        const float percentage = (current_velocity / max_velocity) > 0.f ? (current_velocity / max_velocity) : -(current_velocity / max_velocity);
        m_animations[action]->play(dt, percentage);
    }

    return m_animations[action]->is_done();
}

void AnimationComponent::stop_previos_animation(const std::string & action)
{
    if (m_last_animation != m_animations[action]) {
        if (m_last_animation == nullptr) {
            m_last_animation = m_animations[action];
        }

        m_last_animation->reset();
        m_last_animation = m_animations[action];
    }
}