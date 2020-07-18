#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "playing_field.h"
#include "chunk.h"
#include "tile.h"

namespace drawer {
	void init_drawer();

	void drawPlayingField(const playingField& playing_field);
	void drawPlayingFieldDebug(sf::RenderWindow& window, sf::View& camera, playingField& playing_field, const int window_width, const int window_height);

	void drawChunk(sf::RenderWindow& window, sf::View& camera, chunk& chunk, const int widnow_width, const int window_height);
	void drawChunkDebug(sf::RenderWindow& window, sf::View& camera, chunk& chunk, const int window_width, const int window_height);

	void drawTile();
}