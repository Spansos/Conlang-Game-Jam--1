#pragma once

// headers
#include <vector>
#include <SFML/Graphics.hpp>


class Obstacle : public sf::Drawable {
public:
    Obstacle(sf::FloatRect rect, int state, bool fixed=false);
    void update();
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::FloatRect m_rect;
    int m_state;
    bool m_fixed;
friend class Level;
};


class Level : public sf::Drawable {
public:
    Level(std::vector<Obstacle> obstacles, int statec);
    const std::vector<Obstacle> & getObstacles() const;
    void update();
    sf::FloatRect collides(sf::FloatRect rect) const;
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    int m_current_state;
    int m_statec;
    std::vector<Obstacle> m_obstacles;
};