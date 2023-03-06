#pragma once

// headers
#include <Vector>
#include <SFML/Graphics/RectangleShape.hpp>

class Level {
    public:
        Level();
        Level(std::vector<LevelState>);
        std::vector<LevelState> &getStates();
        LevelState &getState();

    private:
        int state_index;
        std::vector<LevelState> states;
};

class LevelState {
    public:
        LevelState();
        LevelState(std::vector<Obstacle>);
        std::vector<Obstacle> &getObstacles();
    
    private:
        std::vector<Obstacle> obstacles;

};

class Obstacle {
    public:
        sf::IntRect rect;
};