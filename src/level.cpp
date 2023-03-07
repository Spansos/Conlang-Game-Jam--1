#include <level.hpp>

sf::RectangleShape Obstacle::drawshape;

Obstacle::Obstacle(sf::IntRect rect, int state, bool fixed) {
    m_rect = rect;
    m_state = state;
    m_fixed = fixed;
}

Level::Level(std::vector<Obstacle> obstacles) {
    m_obstacles = obstacles;
    m_current_state = 0;
}

int Level::getState() {
    return m_current_state;
}

void Level::setState(int state) {
    m_current_state = state;
}

void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    drawshape.setPosition(m_rect.left, m_rect.top);
    drawshape.setSize(sf::Vector2f(m_rect.width, m_rect.height));
    target.draw(drawshape, states);
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &obstacle : m_obstacles) {
        if (obstacle.m_state == m_current_state || obstacle.m_fixed) {
            target.draw(obstacle, states);
        }
    }
}

