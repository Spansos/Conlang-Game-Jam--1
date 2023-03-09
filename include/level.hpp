#pragma once

// headers
#include <vector>
#include <SFML/Graphics.hpp>


class Obstacle : public sf::Drawable {
    public:
        Obstacle(sf::IntRect rect, int state, bool fixed=false);
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        static sf::RectangleShape drawshape;
        sf::IntRect m_rect;
        int m_state;
        bool m_fixed;
    friend class Level;
};


class Level : public sf::Drawable {
    public:
        Level(std::vector<Obstacle> obstacles);
        void setState(int state);
        int getState();
    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        int m_current_state;
        std::vector<Obstacle> m_obstacles;
};