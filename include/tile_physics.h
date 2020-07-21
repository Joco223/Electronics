#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "tile.h"

namespace tilePhysics {
	void swapTiles(tile& t1, tile& t2);

	void updateTilePhysicsWetSolids(tile& t, std::array<tile*, 8> sTiles);
	void updateTilePhysicsDusts(tile& t, std::array<tile*, 8> sTiles);
	void updateTilePhysicsLiquids(tile& t, std::array<tile*, 8> sTiles);
};