#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

#include "playing_field.h"
#include "chunk.h"
#include "tile.h"
#include "gui/gui.h"
#include "gui/gui_container.h"
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

	void handleMouse(sf::RenderWindow& window, sf::View& camera, sf::Event& event, playingField* playing_field, GUI* gui, const int window_width, const int window_height, const float scale) {
		if (!gui->handleEvent(event)) {
			gui->addEvent("input_handler", "screen", mouseOver);
			if (event.type == sf::Event::MouseButtonPressed) {
				gui->addEvent("input_handler", "screen", leftClick);

				std::vector<chunk*> visibleChunks = playing_field->getVisibleChunks(camera, window_width, window_height, scale);

				for(auto c : visibleChunks) {
					int c_pos_x = c->pos_x*c->screen_size/scale + window_width - camera.getCenter().x;
					int c_pos_y = c->pos_y*c->screen_size/scale + window_height - camera.getCenter().y;
					sf::IntRect chunk_screen;
					chunk_screen.left = c_pos_x;
					chunk_screen.top = c_pos_y;
					chunk_screen.height = c->screen_size/scale;
					chunk_screen.width = c->screen_size/scale;

					if (chunk_screen.contains(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))) {
						for (auto& t : c->tiles) {
							sf::IntRect tile_screen;
							tile_screen.left = c_pos_x + t.pos_x*24/scale;
							tile_screen.top = c_pos_y + t.pos_y*24/scale;
							tile_screen.width = 24/scale;
							tile_screen.height = 24/scale;

							if (tile_screen.contains(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))) {
								if (event.mouseButton.button == 0) {
									t.new_state = 2;
									t.state = 2;
								}else{
									t.lua_path = "metal.lua";
									t.state = 0;
									t.new_state = 0;
									t.type = 1;
									t.new_type = 1;
								}
								break;
							}
						}
						break;
					}
				}
			}
		}
	}
}