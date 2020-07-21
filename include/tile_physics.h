#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "tile.h"

namespace tilePhysics {
	void swapTiles(tile& t1, tile& t2);

	void updateTilePhysics(tile& t, std::array<tile*, 8> sTiles);
};