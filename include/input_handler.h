#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

namespace inputHandler {
	bool scaleAlreadyUpdated = false;

	std::array<bool, 6> pressed_keys = {false, false, false, false, false, false};

	enum keys {
		w,
		s,
		a,
		d,
		q,
		e
	};

	void checkPressedKeys(sf::Event& event) {
		switch(event.key.code) {
			case sf::Keyboard::W: pressed_keys[w] = true; break;
			case sf::Keyboard::S: pressed_keys[s] = true; break;
			case sf::Keyboard::A: pressed_keys[a] = true; break;
			case sf::Keyboard::D: pressed_keys[d] = true; break;
			case sf::Keyboard::Q: pressed_keys[q] = true; break;
			case sf::Keyboard::E: pressed_keys[e] = true; break;
		}
	}

	void checkReleasedKeys(sf::Event& event) {
		switch(event.key.code) {
			case sf::Keyboard::W: pressed_keys[w] = false; break;
			case sf::Keyboard::S: pressed_keys[s] = false; break;
			case sf::Keyboard::A: pressed_keys[a] = false; break;
			case sf::Keyboard::D: pressed_keys[d] = false; break;
			case sf::Keyboard::Q: pressed_keys[q] = false; scaleAlreadyUpdated = false; break;
			case sf::Keyboard::E: pressed_keys[e] = false; scaleAlreadyUpdated = false; break;
		}
	}

	void updateCamera(sf::View& camera, float speed, float& scale) {
		//Movement
		if (pressed_keys[w]) camera.move(     0      , -speed*scale);
		if (pressed_keys[s]) camera.move(     0      ,  speed*scale);
		if (pressed_keys[a]) camera.move(-speed*scale,            0);
		if (pressed_keys[d]) camera.move( speed*scale,            0);

		if (pressed_keys[q] && !scaleAlreadyUpdated && scale > 1.0f/4.0f) { camera.zoom(0.5f); scale /= 2.0f; scaleAlreadyUpdated = true; }
		if (pressed_keys[e] && !scaleAlreadyUpdated && scale < 2.0f)      { camera.zoom(2.0f); scale *= 2.0f; scaleAlreadyUpdated = true; }
	}
}