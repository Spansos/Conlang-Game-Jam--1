#include <vector>
#include <SFML/Graphics.hpp>
#include <level.hpp>


int main() {
  const int gameWidth = 800;
  const int gameHeight = 600;
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Maliante", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(30);

  Level level(
    std::vector<Obstacle>(
      {
        Obstacle(sf::IntRect(12, 54, 402, 20), 0),
        Obstacle(sf::IntRect(15, 20, 40, 40), 0),
        Obstacle(sf::IntRect(0, 542, 32, 102), 0),
        Obstacle(sf::IntRect(0, 0, 100, 100), 1)
      }
    )
  );

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if ( (event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) ) {
        window.close();
        break;
      }
    }
    window.clear(sf::Color(32, 42, 64));
    window.draw(level);
    window.display();
  }

  return EXIT_SUCCESS;
}
