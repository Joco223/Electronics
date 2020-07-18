#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "chunk.h"

class playingField {
private:
	std::vector<chunk> chunks;
public:
	playingField() {};

	void loadPlayingField(const std::string& file_path);
	void generateChunksSquare(const int width, const int height, const int chunk_size);
	std::vector<chunk*> getVisibleChunks(sf::View& camera, const int window_width, const int window_height);
};