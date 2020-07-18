#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "tile.h"

class chunk {
private:
	std::vector<tile> tiles;
public:
	int pos_x, pos_y, size;

	chunk();
	chunk(const int pos_x_, const int pos_y_, const int size_);

	void updateTiles();
};