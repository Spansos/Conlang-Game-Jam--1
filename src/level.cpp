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

sf::FloatRect Obstacle::getRect() {
    return m_rect;
}

bool Obstacle::is_hazard() {
    return m_hazard;
}

Level::Level() {
    m_obstacles = std::vector<Obstacle>{};
    m_statec = 0;
    m_current_state = 0;
    m_checkpoints = std::vector<sf::FloatRect>{};
    m_cur_checkpoint = 0;
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
    if (!file) {
        return;
    }

    file >> m_statec;

    m_obstacles.clear();
    float x, y, width, height;
    int state, hazard, fixed;
    do {
        file >> x >> y >> width >> height >> state >> hazard >> fixed;
        m_obstacles.push_back(
            Obstacle({x, y, width, height}, state, hazard, fixed)
        );
    } while (file.peek() != '\n');

    m_checkpoints.clear();
    do {
        file >> x >> y >> width >> height;
        m_checkpoints.push_back(
            sf::FloatRect(x, y, width, height)
        );
    } while (file.peek() != '\n' && file.peek() != EOF);

    file.close();
}

const std::vector<Obstacle> & Level::getObstacles() const {
    return (std::vector<Obstacle> &)m_obstacles;
}

void Level::nextstate() {
    m_current_state = (m_current_state+1)%m_statec;
}

Obstacle Level::collides(sf::FloatRect rect) const {
    for (const auto & obstacle : m_obstacles) {
        if ((obstacle.m_state == m_current_state || obstacle.m_fixed)
            && rect.intersects(obstacle.m_rect)) {
            return obstacle;
        }
    }
    return Obstacle(sf::FloatRect(0, 0, 0, 0), 0);
}

void Level::update_checkpoint(const Player &player) {
    for (int i=0; i<m_checkpoints.size(); i++) {
        if (player.getRect().intersects(m_checkpoints[i])) {
            m_cur_checkpoint = i;
            break;
        }
    }
}

void Level::reset_player(Player &player) const {
    sf::FloatRect checkpoint = m_checkpoints[m_cur_checkpoint];
    sf::Vector2f spawn_pos = {checkpoint.left+checkpoint.width/2, checkpoint.top+checkpoint.height/2};
    player.setPos({spawn_pos.x-player.getRect().width/2, spawn_pos.y-player.getRect().height/2});
    player.reset_all();
}

void Level::reset_level(Player &player) {
    m_cur_checkpoint = 0;
    m_current_state = 0;
    reset_player(player);
}

bool Level::is_finished() {
    return (m_cur_checkpoint == (m_checkpoints.size() - 1) || m_checkpoints.size() == 0);
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

