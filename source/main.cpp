#include <iostream>
#include <SFML/Graphics.hpp>

#include "input_handler.h"
#include "playing_field.h"
#include "drawer.h"

constexpr int width = 1280;
constexpr int height = 720;

int main(int argc, char** argv) {

	playingField playing_field;
	playing_field.generateChunksSquare(8, 8, 8);

	sf::RenderWindow window(sf::VideoMode(width, height), "Electronics");
	window.setFramerateLimit(60);
	sf::View camera = window.getDefaultView();

	bool keyWasUpdated = false;

	drawer::init_drawer();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}else if (event.type == sf::Event::KeyPressed) {
				inputHandler::checkPressedKeys(event);
				keyWasUpdated = true;
			}else if (event.type == sf::Event::KeyReleased) {
				inputHandler::checkReleasedKeys(event);
				keyWasUpdated = true;
			}
		}

		if (keyWasUpdated) {
			inputHandler::updateCamera(camera, 5);
		}

		window.setView(camera);
		window.clear(sf::Color(50, 50, 50, 255));

		//All the drawing goes here
		drawer::drawPlayingFieldDebug(window, camera, playing_field, width, height);

		window.display();
	}

	return 0;
}