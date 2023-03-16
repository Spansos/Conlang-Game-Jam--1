#include <level.hpp>
#include <player.hpp>
#include <fstream>
#include <iostream>

Obstacle::Obstacle(sf::FloatRect rect, int state, bool hazard, bool fixed) {
    m_rect = rect;
    m_state = state;
    m_fixed = fixed;
    m_hazard = hazard;
}

Level::Level(std::vector<Obstacle> obstacles, std::vector<sf::FloatRect> checkpoints, int statec) {
    m_obstacles = obstacles;
    m_statec = statec;
    m_current_state = 0;
    m_checkpoints = checkpoints;
    m_cur_checkpoint = 0;
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
        if ((obstacle.m_state == m_current_state || obstacle.m_fixed)
            && rect.intersects(obstacle.m_rect)) {
            return obstacle.m_rect;
        }
    }
    return sf::FloatRect(0, 0, 0, 0);
}

void Level::update_checkpoint(const Player &player) {
    for (int i=0; i<m_checkpoints.size(); i++) {
        if (player.getRect().intersects(m_checkpoints[i])) {
            m_cur_checkpoint = i;
            break;
        }
    }
}

void Level::reset_player(Player &player) {
    sf::FloatRect checkpoint = m_checkpoints[m_cur_checkpoint];
    sf::Vector2f spawn_pos = {checkpoint.left+checkpoint.width/2, checkpoint.top+checkpoint.height/2};
    player.setPos({spawn_pos.x-player.getRect().width/2, spawn_pos.y-player.getRect().height/2});
}

void Level::reset_level(Player &player) {

}

void draw_rect(const sf::FloatRect rect, sf::Color color, sf::RenderTarget &target, sf::RenderStates states) {
    static sf::RectangleShape rectshape;
    rectshape.setFillColor(color);
    rectshape.setPosition(rect.left, rect.top);
    rectshape.setSize(sf::Vector2f(rect.width, rect.height));
    target.draw(rectshape, states);
}


void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    draw_rect(
        m_rect,
        (m_hazard) ? sf::Color::Red : sf::Color::White,
        target,
        states
    );
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i=0; i<m_checkpoints.size(); i++) {
        sf::Color color;
        if (i==m_checkpoints.size()-1) {
            color = sf::Color::Green;
        } else if (i == m_cur_checkpoint) {
            color = {90, 116, 128};
        } else {
            color = {48, 64, 80};
        }
        draw_rect(m_checkpoints[i], color, target, states);
    }
    for (auto &obstacle : m_obstacles) {
        if (obstacle.m_state == m_current_state || obstacle.m_fixed) {
            target.draw(obstacle, states);
        }
    }
}

