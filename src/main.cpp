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


	Level level{
		std::vector<Obstacle>{{
			Obstacle{{20, 400, 400, 20}, 0},
			Obstacle{{570, 150, 20, 320}, 0},
			Obstacle{{420, 390, 150, 20}, 0},
			Obstacle{{0, 480, 600, 20}, 1},
			Obstacle{{570, 50, 20, 180}, 1},
			Obstacle{{0, 0, 100, 100}, 0, 1}
		}},
		std::vector<sf::FloatRect>{{
			{200, 100, 70, 90},
			{500, 300, 25, 40}
		}},
		2
	};
	// level.load_from_file("resources/levels/1.txt");
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
				level.reset_player(player);
			}
		}
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