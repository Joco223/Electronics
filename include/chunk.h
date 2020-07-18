#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

#include "tile.h"
#include "lua_vm.h"
class chunk {
public:
	std::vector<tile> tiles;
	int pos_x, pos_y, size, screen_size;

	chunk();
	chunk(const int pos_x_, const int pos_y_, const int size_);

	void updateTiles(std::array<chunk*, 8>& surroundingChunks);
};