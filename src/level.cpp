#include <level.hpp>
#include <fstream>
#include <iostream>

Obstacle::Obstacle(sf::FloatRect rect, int state, int hazard, bool fixed) {
    m_rect = rect;
    m_state = state;
    m_fixed = fixed;
    m_hazard = hazard;
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
    int vals[12];
    while (!file.eof()) {
        file.getline(line, 128);
        std::cout << line << std::endl;
    }
    
    file.close();
}

const std::vector<Obstacle> & Level::getObstacles() const {
    return (std::vector<Obstacle> &)m_obstacles;
}

void Level::nextstate() {
    m_current_state = (m_current_state+1)%m_statec;
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

// obrect = obstacle rect
void drawhazard(sf::FloatRect obrect, int hazard, sf::RenderTarget &target, sf::RenderStates states) {
    static sf::ConvexShape triangle(3);

    triangle.setFillColor(sf::Color::Red);

    triangle.setPoint(0, {0, 0});
    triangle.setPoint(1, {obrect.width, obrect.height/2});
    triangle.setPoint(2, {0, obrect.height});
    
    target.draw(triangle, states);
}

void drawobrect(sf::FloatRect obrect, sf::RenderTarget &target, sf::RenderStates states) {
    static sf::RectangleShape rectshape;
    rectshape.setFillColor(sf::Color::White);
    // drawshape.setFillColor(sf::Color(32, 42, 64));
    rectshape.setPosition(obrect.left, obrect.top);
    rectshape.setSize(sf::Vector2f(obrect.width, obrect.height));
    target.draw(rectshape, states);
}

void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (m_hazard) {
        drawhazard(m_rect, m_hazard, target, states);
    } else {
        drawobrect(m_rect, target, states);
    }
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &obstacle : m_obstacles) {
        if (obstacle.m_state == m_current_state || obstacle.m_fixed) {
            target.draw(obstacle, states);
        }
    }
}

