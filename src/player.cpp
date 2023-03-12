#include <player.hpp>
#include <iostream>
#include <cstring>

Player::Player(sf::FloatRect rect) {
    m_rect = rect;

    m_vel = sf::Vector2f(0, 0);
    m_coyote_time_frames = 0;
    m_jump_buffer_frames = 0;
    std::memset(m_contacts, 0, sizeof(bool) * 4);
}


void Player::update(const Level &level) {
    // input
    float d_vel_x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) d_vel_x++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) d_vel_x--;
    // better walk on ground
    d_vel_x *= (m_contacts[3] + .5);
    // update vel
    m_vel.x += d_vel_x;
    if (m_contacts[3]) m_vel.x *= .9; else m_vel.x *= .95;

    // jump
    float d_vel_y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) m_jump_buffer_frames = 2; // bruh. i implemented jump buffering only for it to be used for a single extra frame
    if (m_contacts[3]) m_coyote_time_frames = 4;
    if (m_jump_buffer_frames && m_coyote_time_frames) {
        m_jump_buffer_frames = 0;
        m_coyote_time_frames = 0;
        d_vel_y -= 48;
    }
    if (m_jump_buffer_frames > 0) m_jump_buffer_frames--;
    if (m_coyote_time_frames > 0) m_coyote_time_frames--;
    // gravity
    d_vel_y += 2;
    // update vel
    m_vel.y += d_vel_y;
    m_vel.y *= .95;

    // update pos
    move_and_collide(level);
}


void Player::setPos(sf::Vector2f pos) {
    m_rect.left = pos.x;
    m_rect.top = pos.y;
}


void Player::move_and_collide(const Level &level) {
    std::memset(m_contacts, 0, sizeof(bool) * 4);

    m_rect.left += m_vel.x;
    sf::FloatRect col_with = level.collides(m_rect);
    if (col_with.height) {
        if (m_vel.x < 0) {
            m_contacts[0] = true;
            m_rect.left = col_with.left+col_with.width;
            m_vel.x = 0;
        } else {
            m_contacts[1] = true;
            m_rect.left = col_with.left - m_rect.width;
            m_vel.x = 0;
        }
    }

    m_rect.top += m_vel.y;
    col_with = level.collides(m_rect);
    if (col_with.height) {
        if (m_vel.y < 0) {
            m_contacts[2] = true;
            m_rect.top = col_with.top+col_with.height;
            m_vel.y = 0;
        } else {
            m_contacts[3] = true;
            m_rect.top = col_with.top - m_rect.height;
            m_vel.y = 0;
        }
    }
}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    static sf::RectangleShape drawshape;
    drawshape.setFillColor(sf::Color(200, 200, 200));
    drawshape.setSize(sf::Vector2f(m_rect.width, m_rect.height));
    drawshape.setPosition(m_rect.left, m_rect.top);
    target.draw(drawshape, states);
}