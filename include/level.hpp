#pragma once

// headers
#include <vector>
#include <SFML/Graphics.hpp>

class Player;

class Obstacle : public sf::Drawable {
public:
    Obstacle(sf::FloatRect rect, int state, bool hazard=false, bool fixed=false);
    sf::FloatRect getRect();
    bool is_hazard();
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::FloatRect m_rect;
    int m_state;
    bool m_fixed;
    bool m_hazard;
friend class Level;
};


class Level : public sf::Drawable {
public:
    Level();
    Level(std::vector<Obstacle> obstacles, std::vector<sf::FloatRect> checkpoints, int statec);
    void load_from_file(std::string filename);
    const std::vector<Obstacle> & getObstacles() const;
    void nextstate();
    Obstacle collides(sf::FloatRect rect) const;
    void update_checkpoint(const Player &player);
    void reset_player(Player &player) const;
    void reset_level(Player &player);
    bool is_finished();
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    int m_cur_checkpoint;
    int m_current_state;
    int m_statec;
    std::vector<sf::FloatRect> m_checkpoints;
    std::vector<Obstacle> m_obstacles;
};