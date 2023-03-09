#include <level.hpp>
#include <sfml/Graphics.hpp>

class Player : public sf::Drawable {
public:
    Player(sf::FloatRect rect);
    void update(const Level &level);
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(const Level &level);
    bool m_grounded;
    sf::FloatRect m_rect;
    sf::Vector2f m_vel;
};