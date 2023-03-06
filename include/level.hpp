#pragma once

// headers
#include <Vector>

class Level {
    public:
        Level();
        Level(std::vector<WorldState>);
        std::vector<WorldState> &getStates();
        // getState();
};

class WorldState {
    public:
        WorldState();
        WorldState(std::vector<Obstacle>);

};

class Obstacle {

};