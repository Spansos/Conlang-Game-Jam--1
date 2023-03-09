#include <player.hpp>
#include <iostream>


void Player::update(const Level &level) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_vel.x += 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_vel.x -= 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_grounded) m_vel.y = -48;

    m_vel.y += 2;

    m_vel.x *= .95;
    m_vel.y *= .95;

    move(level);
}

void Player::move(const Level & level) {
    m_rect.left += m_vel.x;
    sf::FloatRect col_with = level.collides(m_rect);
    if (col_with.height) {
        if (m_vel.x < 0) {
            m_rect.left = col_with.left+col_with.width;
            m_vel.x = 0;
        } else {
            m_rect.left = col_with.left - m_rect.width;
            m_vel.x = 0;
        }
    }

    m_grounded = false;
    m_rect.top += m_vel.y;
    col_with = level.collides(m_rect);
    if (col_with.height) {
        if (m_vel.y < 0) {
            m_rect.top = col_with.top+col_with.height;
            m_vel.y = 0;
        } else {
            m_grounded = true;
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