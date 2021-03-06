#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "chunk.h"

class playingField {
private:
	std::vector<std::array<chunk*, 8>> sChunksCached;
	int width, height;
public:
	std::vector<chunk> chunks;

	playingField() : width(0), height(0) {};

	void loadPlayingField(const std::string& file_path);
	void generateChunksSquare(const int width_, const int height_, const int chunk_size);
	std::vector<chunk*> getVisibleChunks(sf::View& camera, const int window_width, const int window_height, const float scale);
	void generateSChunksCached();
	void updateChunks();
};