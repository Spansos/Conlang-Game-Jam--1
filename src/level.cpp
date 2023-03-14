#include <level.hpp>
#include <fstream>


Obstacle::Obstacle(sf::FloatRect rect, int state, bool fixed) {
    m_rect = rect;
    m_state = state;
    m_fixed = fixed;
}

Level::Level(std::vector<Obstacle> obstacles, int statec) {
    m_obstacles = obstacles;
    m_statec = statec;
    m_current_state = 0;
}

void Level::load_from_file(std::string filename) {
    std::ifstream file;
    file.open(filename);
    char line[128];
    file.getline(line, 128);
    
    file.close();
}

const std::vector<Obstacle> & Level::getObstacles() const {
    return (std::vector<Obstacle> &)m_obstacles;
}

void Level::update() {
    static bool spaceheld;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!spaceheld) {
            m_current_state = (m_current_state+1)%m_statec;
        }
        spaceheld = true;
    } else {
        spaceheld = false;
    }
}

sf::FloatRect Level::collides(sf::FloatRect rect) const {
    for (const auto & obstacle : m_obstacles) {
        if (obstacle.m_state == m_current_state
            && rect.intersects(obstacle.m_rect)) {
            return obstacle.m_rect;
        }
    }
    return sf::FloatRect(0, 0, 0, 0);
}

void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    static sf::RectangleShape drawshape;
    drawshape.setFillColor(sf::Color::White);
    // drawshape.setFillColor(sf::Color(32, 42, 64));
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

