#include "lua_vm.h"

namespace luaVM {
	lua_State* L = nullptr;

	bool checkVM(lua_State* L, int r) {
		if (r != LUA_OK) {
			std::string error_msg = lua_tostring(L, -1);
			std::cerr << error_msg << '\n';
			return false;
		}
		return true;
	}

	void initLuaVM() {
		L = luaL_newstate();
		luaL_openlibs(L);
	}

	std::array<std::string, 16> global_names = {
		"TopLeftHeat" , "TopLeftState" , "TopHeat"        , "TopState"        ,
		"TopRightHeat", "TopRightState", "LeftHeat"       , "LeftState"       ,
		"RightHeat"   , "RightState"   , "BottomLeftHeat" , "BottomLeftState" ,
		"BottomHeat"  , "BottomState"  , "BottomRightHeat", "BottomRightState"
	};

	int total = 0;

	void updateTile(tile& t, std::array<tile*, 8>& sTiles) {
		lua_settop(L, 0);

		for (int i = 0; i < 8; i++) {
			if (sTiles[i] != nullptr) {
				lua_pushinteger(L, sTiles[i]->heat);
				lua_setglobal(L, global_names[i*2].c_str());
				lua_pushinteger(L, sTiles[i]->state);
				lua_setglobal(L, global_names[i*2 + 1].c_str());
			}else{
				lua_pushinteger(L, 0);
				lua_setglobal(L, global_names[i*2].c_str());
				lua_pushinteger(L, 0);
				lua_setglobal(L, global_names[i*2 + 1].c_str());
			}
		}

		//Tile heat
		lua_pushinteger(L, t.heat);
		lua_setglobal(L, "LocalHeat");
		//Tile state
		lua_pushinteger(L, t.state);
		lua_setglobal(L, "LocalState");
		//Tile color red
		lua_pushinteger(L, 255);
		lua_setglobal(L, "LocalRed");
		//Tile color green
		lua_pushinteger(L, 255);
		lua_setglobal(L, "LocalGreen");
		//Tile color blue
		lua_pushinteger(L, 255);
		lua_setglobal(L, "LocalBlue");

		luaL_dofile(L, t.lua_path.c_str());

		lua_getglobal(L, "LocalHeat");
		t.new_heat = lua_tonumber(L, -1);
		lua_getglobal(L, "LocalState");
		t.new_state = lua_tonumber(L, -1);

		lua_getglobal(L, "LocalRed");
		int red = lua_tonumber(L, -1);
		lua_getglobal(L, "LocalGreen");
		int green = lua_tonumber(L, -1);
		lua_getglobal(L, "LocalBlue");
		int blue = lua_tonumber(L, -1);

		t.color = sf::Color(red, green, blue, 255);
	}

	void deInitVM() {
		lua_close(L);
	}
}