#include <iostream>
#include <SFML/Graphics.hpp>

#include "input_handler.h"

int main(int argc, char** argv) {

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Electronics");
	window.setFramerateLimit(60);
	sf::View camera = window.getDefaultView();

	while (window.isOpen()) {
		sf::Event Event;
		while (window.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed) {
				window.close();
			}else if (Event.type == sf::Event::KeyPressed) {

			}else if (Event.type == sf::Event::KeyReleased) {

			}
		}

		window.setView(camera);
		window.clear();

		//All the drawing goes here

		window.display();
	}

	return 0;
}