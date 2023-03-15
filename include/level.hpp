#pragma once

// headers
#include <vector>
#include <SFML/Graphics.hpp>


class Obstacle : public sf::Drawable {
public:
    Obstacle(sf::FloatRect rect, int state, int hazard=0, bool fixed=false);
    void update();
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::FloatRect m_rect;
    int m_state;
    bool m_fixed;
    int m_hazard; // 0 is no hazard, 1 through 4 are left, right, up and down facing spikes
friend class Level;
};


class Level : public sf::Drawable {
public:
    Level() = default;
    Level(std::vector<Obstacle> obstacles, int statec);
    void load_from_file(std::string filename);
    const std::vector<Obstacle> & getObstacles() const;
    void nextstate();
    sf::FloatRect collides(sf::FloatRect rect) const;
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    int m_current_state;
    int m_statec;
    std::vector<Obstacle> m_obstacles;
};