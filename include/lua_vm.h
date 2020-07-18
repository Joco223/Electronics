#pragma once

extern "C" {
#include "lua5.3/lua.h"
#include "lua5.3/lauxlib.h"
#include "lua5.3/lualib.h"
}

#include <string>
#include <iostream>
#include <array>

#include "tile.h"

namespace luaVM {
	bool checkVM(lua_State* L, int r);
	void initLuaVM();
	void updateTile(tile& t, std::array<tile*, 8>& sTiles);
	void deInitVM();
}