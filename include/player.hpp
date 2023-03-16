#pragma once

#include <sfml/Graphics.hpp>

class Level;

class Player : public sf::Drawable {
public:
    Player(sf::FloatRect rect);
    void update(Level &level);
    void setPos(sf::Vector2f pos);
    void setVel(sf::Vector2f vel);
    sf::FloatRect getRect() const;
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move_and_collide(const Level &level);
    void collide(const Level &level);
    sf::FloatRect m_rect;
    sf::Vector2f m_vel;
    int m_jump_buffer_frames;
    int m_coyote_times_frames[4];
    bool m_is_jumping;
    bool m_contacts[4]; // keeps track of which directions are currently touching obstacles. order = left, right, top, bottom
};