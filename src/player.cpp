#include <player.hpp>
#include <level.hpp>
#include <iostream>
#include <cstring>

Player::Player(sf::FloatRect rect) {
    m_rect = rect;

    reset_all();
}

void Player::reset_all() {
    m_vel = sf::Vector2f(0, 0);
    m_jump_buffer_frames = 0;
    m_is_jumping = false;
    std::memset(m_coyote_times_frames, 0, sizeof(int) * 4);
    std::memset(m_contacts, 0, sizeof(bool) * 4);
}

void Player::update(Level &level) {
    // input
    float in_x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) in_x++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) in_x--;
    // better walk on ground
    in_x *= (m_contacts[3] + .7) * 1.6;
    m_vel.x += in_x;
    // friction
    if (m_contacts[3]) m_vel.x *= .79; else m_vel.x *= .9;

    // jump input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_jump_buffer_frames = 4;
    }
    else {
        m_is_jumping = false;
    }
    // set coyote time
    for (int i=0; i<4; i++) {
        if (m_contacts[i]) {
            m_coyote_times_frames[i] = (i < 2) ? 12 : 4;
        }
    }
    // do jump (and change level state)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_jump_buffer_frames && (m_coyote_times_frames[0] || m_coyote_times_frames[1] || m_coyote_times_frames[3]) && !m_is_jumping) {
        m_vel.y -= 16;
        if (!m_contacts[3]) {
            if (m_coyote_times_frames[0]) m_vel.x += 12;
            if (m_coyote_times_frames[1]) m_vel.x -= 12;
        }
        m_is_jumping = true;
        std::memset(m_coyote_times_frames, 0, sizeof(int) * 4);
        m_jump_buffer_frames = 0;
        level.nextstate();
    }
    if (m_jump_buffer_frames > 0) m_jump_buffer_frames--;
    for (int i=0; i<4; i++) {
        if (m_coyote_times_frames[i] > 0) m_coyote_times_frames[i]--;
    }
    // gravity
    if (m_is_jumping) {
        m_vel.y += .35;
    } else {
        m_vel.y += .7;
    }
    // friction
    if ((m_contacts[0] || m_contacts[1]) && !m_is_jumping) {
        m_vel.y *= .7;
    } else {
        m_vel.y *= .96;
    }

    // update pos
    move_and_collide(level);
    // update checkpoint
    level.update_checkpoint(*this);
}


void Player::setPos(sf::Vector2f pos) {
    m_rect.left = pos.x;
    m_rect.top = pos.y;
}

void Player::setVel(sf::Vector2f vel) {
    m_vel = vel;
}

sf::FloatRect Player::getRect() const {
    return m_rect;
}

void Player::move_and_collide(const Level &level) {
    collide(level);
    std::memset(m_contacts, 0, sizeof(bool) * 4);

    m_rect.left += m_vel.x;
    Obstacle col_obs = level.collides(m_rect);
    sf::FloatRect col_rect = col_obs.getRect();
    if (col_obs.is_hazard()) {
        level.reset_player(*this);
        return;
    }
    if (col_rect.height) {
        if (m_vel.x < 0) {
            m_contacts[0] = true;
            m_rect.left = col_rect.left+col_rect.width;
            m_vel.x = 0;
        } else {
            m_contacts[1] = true;
            m_rect.left = col_rect.left - m_rect.width;
            m_vel.x = 0;
        }
    }

    m_rect.top += m_vel.y;
    col_obs = level.collides(m_rect);
    col_rect = col_obs.getRect();
    if (col_obs.is_hazard()) {
        level.reset_player(*this);
        return;
    }
    if (col_rect.height) {
        if (m_vel.y < 0) {
            m_contacts[2] = true;
            m_rect.top = col_rect.top+col_rect.height;
            m_vel.y = 0;
        } else {
            m_contacts[3] = true;
            m_rect.top = col_rect.top - m_rect.height;
            m_vel.y = 0;
        }
    }
}

void Player::collide(const Level &level) {
    Obstacle col_obs = level.collides(m_rect);
    sf::FloatRect col_rect = col_obs.getRect();
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