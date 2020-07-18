#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

namespace inputHandler {
	std::array<bool, 4> pressed_keys = {false, false, false, false};

	enum keys {
		w,
		s,
		a,
		d
	};

	void checkPressedKeys(sf::Event& event) {
		switch(event.key.code) {
			case sf::Keyboard::W: pressed_keys[w] = true; break;
			case sf::Keyboard::S: pressed_keys[s] = true; break;
			case sf::Keyboard::A: pressed_keys[a] = true; break;
			case sf::Keyboard::D: pressed_keys[d] = true; break;
		}
	}

	void checkReleasedKeys(sf::Event& event) {
		switch(event.key.code) {
			case sf::Keyboard::W: pressed_keys[w] = false; break;
			case sf::Keyboard::S: pressed_keys[s] = false; break;
			case sf::Keyboard::A: pressed_keys[a] = false; break;
			case sf::Keyboard::D: pressed_keys[d] = false; break;
		}
	}

	void updateCamera(sf::View& camera, float speed) {
		if (pressed_keys[w]) camera.move(     0, -speed);
		if (pressed_keys[s]) camera.move(     0,  speed);
		if (pressed_keys[a]) camera.move(-speed,      0);
		if (pressed_keys[d]) camera.move( speed,      0);
	}
}