#include <player.hpp>
#include <iostream>
#include <cstring>

Player::Player(sf::FloatRect rect) {
    m_rect = rect;

    m_vel = sf::Vector2f(0, 0);
    m_coyote_time_frames = 0;
    m_jump_buffer_frames = 0;
    m_is_jumping = false;
    std::memset(m_contacts, 0, sizeof(bool) * 4);
}


void Player::update(const Level &level) {
    // input
    float in_x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) in_x++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) in_x--;
    // better walk on ground
    in_x *= (m_contacts[3] + 1) * 2;
    m_vel.x += in_x;
    // friction
    if (m_contacts[3]) m_vel.x *= .8; else m_vel.x *= .9;

    // jump input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_jump_buffer_frames = 1;
    }
    else {
        m_is_jumping = false;
    }
    // set coyote time
    if (m_contacts[3] || m_contacts[0] || m_contacts[1]) {
        m_coyote_time_frames = 4;
    }
    // do jump
    if (m_jump_buffer_frames && m_coyote_time_frames && !m_is_jumping) {
        m_jump_buffer_frames = 0;
        m_coyote_time_frames = 0;
        m_vel.y -= 28;
        m_is_jumping = true;
        if (!m_contacts[3]) {
            if (m_contacts[0]) m_vel.x += 16;
            if (m_contacts[1]) m_vel.x -= 16;
        }
    }
    if (m_jump_buffer_frames > 0) m_jump_buffer_frames--;
    if (m_coyote_time_frames > 0) m_coyote_time_frames--;
    // gravity
    if (m_is_jumping) {
        m_vel.y += 1;
    } else {
        m_vel.y += 2;
    }
    // friction
    if ((m_contacts[0] || m_contacts[1]) && !m_is_jumping) {
        m_vel.y *= .6;
    } else {
        m_vel.y *= .95;
    }

    // update pos
    move_and_collide(level);
}


void Player::setPos(sf::Vector2f pos) {
    m_rect.left = pos.x;
    m_rect.top = pos.y;
}


void Player::move_and_collide(const Level &level) {
    collide(level);
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

void Player::collide(const Level &level) {
    sf::FloatRect col_rect = level.collides(m_rect);
    if (!col_rect.height) {
        return;
    }
    float d_up      = (m_rect.top)-(col_rect.top-m_rect.height);
    float d_left    = (m_rect.left)-(col_rect.left-m_rect.width);
    float d_bottom  = (col_rect.top+col_rect.height+m_rect.height)-(m_rect.top+m_rect.height);
    float d_right   = (col_rect.left+col_rect.width+m_rect.width)-(m_rect.left+m_rect.width);

    float min_d = std::min({d_up, d_left, d_bottom, d_right});

    if (d_up == min_d) {
        m_rect.top = col_rect.top-m_rect.height;
    } else if (d_left == min_d) {
        m_rect.left = col_rect.left-m_rect.width;
    } else if (d_bottom == min_d) {
        m_rect.top = col_rect.top+col_rect.height;
    } else if (d_right == min_d) {
        m_rect.left = col_rect.left+col_rect.width;
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    static sf::RectangleShape drawshape;
    drawshape.setFillColor(sf::Color(200, 200, 200));
    drawshape.setSize(sf::Vector2f(m_rect.width, m_rect.height));
    drawshape.setPosition(m_rect.left, m_rect.top);

    target.draw(drawshape, states);
}