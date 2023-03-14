#include <vector>
#include <SFML/Graphics.hpp>
#include <level.hpp>
#include <player.hpp>

#include <iostream>

int main() {
	const int gameWidth = 800;
	const int gameHeight = 600;
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Maliante", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);

	Level level;
	level.load_from_file("resources/levels/1.txt");
	Player player(sf::FloatRect(40, 20, 24, 48));

	int framec = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
				window.close();
				break;
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R)) {
				player.setPos(sf::Vector2f(40, 20));
			}
		}
		level.update();
		player.update(level);

		window.clear(sf::Color(32, 42, 64));
		// window.clear(sf::Color::White);
		window.draw(level);
		window.draw(player);
		window.display();

		framec++;
	}

	return EXIT_SUCCESS;
}