#pragma once

#include "sol.hpp"

#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <sstream>

#include "tile.h"

namespace luaVM {
	void initVM();
	void updateTile(tile& t, std::array<tile*, 8>& sTiles);
}