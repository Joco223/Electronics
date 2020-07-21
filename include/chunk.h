#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

#include "tile.h"
#include "lua_vm.h"
#include "tile_physics.h"

class chunk {
private:
	std::vector<std::array<tile*, 8>> sTilesCached;
public:
	std::vector<tile> tiles;
	int pos_x, pos_y, size, screen_size;

	chunk();
	chunk(const int pos_x_, const int pos_y_, const int size_);

	void generateSTilesCached(std::array<chunk*, 8>& sChunks);
	void updateTiles(std::array<chunk*, 8>& sChunks);
	void updateTilePhysicsWetSolids(std::array<chunk*, 8>& sChunks);
	void updateTilePhysicsDusts(std::array<chunk*, 8>& sChunks);
	void updateTilePhysicsLiquids(std::array<chunk*, 8>& sChunks);
};