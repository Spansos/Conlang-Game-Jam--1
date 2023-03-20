#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <level.hpp>
#include <player.hpp>

#include <iostream>


#define END_LEVEL 9

int main() {
	const int gameWidth = 800;
	const int gameHeight = 600;
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Maliante", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);


	Level level;
	Player player(sf::FloatRect(0, 0, 24, 48));

	int level_n = 0;
	bool skip = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
				window.close();
				break;
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R) && (level_n != END_LEVEL)) {
				level.reset_player(player);
			}
			// if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P)) {
			// 	skip = true;
			// }
		}
		if (player.getRect().top > 600 && level_n != END_LEVEL) {
			level.reset_player(player);
		}
		if ((level.is_finished() || skip) && level_n != END_LEVEL) {
			skip = false;
			level_n++;
			std::string path = "resources/levels/" + std::to_string(level_n) + ".txt";
			level.load_from_file(path);
			level.reset_level(player);
		}

		player.update(level);

		window.setView(sf::View({player.getRect().left+12-400, 0, 800, 600}));

		window.clear(sf::Color(32, 42, 64));
		window.draw(level);
		window.draw(player);
		window.display();
	}

	return EXIT_SUCCESS;
}