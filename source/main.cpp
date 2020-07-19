#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

#include "input_handler.h"
#include "playing_field.h"
#include "drawer.h"
#include "lua_vm.h"

constexpr int width = 1280;
constexpr int height = 720;

int main(int argc, char** argv) {
	playingField playing_field;
	playing_field.generateChunksSquare(4, 4, 8);
	playing_field.generateSChunksCached();
	float scale = 1.0f;

	sf::RenderWindow window(sf::VideoMode(width, height), "Electronics");
	//window.setFramerateLimit(60);
	sf::View camera = window.getDefaultView();

	bool keyWasUpdated = false;

	drawer::initDrawer();

	auto start = std::chrono::high_resolution_clock::now();
	int frameCounter = 0;

	luaVM::initVM();

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
			inputHandler::updateCamera(camera, 5, scale);
		}

		playing_field.updateChunks();

		window.setView(camera);
		window.clear(sf::Color(50, 50, 50, 255));

		//All the drawing goes here
		drawer::drawPlayingField(window, camera, playing_field, width, height, scale);
		//drawer::drawPlayingFieldDebug(window, camera, playing_field, width, height, scale);

		window.display();

		if (frameCounter == 100) {
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			start = std::chrono::high_resolution_clock::now();
			std::cout << round(1000.0/(duration.count()/100.0)) << " FPS on average.\n";
			frameCounter = 0;
		}else{
			frameCounter++;
		}	
	}

	return 0;
}