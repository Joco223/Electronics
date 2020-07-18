#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "playing_field.h"
#include "chunk.h"
#include "tile.h"

namespace drawer {
	void initDrawer();

	void drawPlayingField(sf::RenderWindow& window, sf::View& camera, playingField& playing_field, const int window_width, const int window_height, const float scale);
	void drawPlayingFieldDebug(sf::RenderWindow& window, sf::View& camera, playingField& playing_field, const int window_width, const int window_height, const float scale);

	void drawChunk(sf::RenderWindow& window, chunk& chunk, const int window_width, const int window_height);
	void drawChunkDebug(sf::RenderWindow& window, chunk& chunk, const int window_width, const int window_height);

	void drawTile(sf::RenderWindow& window, tile& t, chunk* c, const int window_width, const int window_height);
}