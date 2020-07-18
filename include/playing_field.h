#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "chunk.h"

class playingField {
private:
	std::vector<chunk> chunks;
	int width, height;
public:
	playingField() : width(0), height(0) {};

	void loadPlayingField(const std::string& file_path);
	void generateChunksSquare(const int width_, const int height_, const int chunk_size);
	std::vector<chunk*> getVisibleChunks(sf::View& camera, const int window_width, const int window_height, const float scale);
	void updateChunks();
};