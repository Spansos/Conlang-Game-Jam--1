#include <SFML/Graphics.hpp>
#include <iostream>


int main() {
  const int gameWidth = 800;
  const int gameHeight = 600;
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Dark Forest", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(30);

  // sf::Texture texture;
  // if (!texture.loadFromFile("")) {
  //   return EXIT_FAILURE;
  // };

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
    window.display();
  }

  return EXIT_SUCCESS;
}
