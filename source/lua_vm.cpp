#include "lua_vm.h"

namespace luaVM {
	lua_State* L = nullptr;

	std::vector<std::string> loadedFiles;
	std::vector<std::string> loadedFileNames;

	std::string loadFile(const std::string& path) {
		std::fstream file;
		file.open(path.c_str());
		if (file.is_open()) {
			std::ostringstream ss;
			ss << file.rdbuf();
			return ss.str();
		}else{
			std::cerr << "Unable to load file: " << path << '\n';
			return "";
		}
	}

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

	int findIndex(const std::string& path) {
		int index = -1;
		for (int i = 0; i < loadedFileNames.size(); i++) {
			if (path == loadedFileNames[i]) {
				index = i;
				break;
			}
		}
		return index;
	}

	void updateTile(tile& t, std::array<tile*, 8>& sTiles) {
		if (t.lua_index == -1) {
			int index = findIndex(t.lua_path);

			if (index == -1) {
				t.lua_index = loadedFiles.size();
				loadedFiles.push_back(loadFile(t.lua_path));
				loadedFileNames.push_back(t.lua_path);
			}else{
				t.lua_index = index;
			}			
		}

		luaL_dostring(L, loadedFiles[t.lua_index].c_str());
		lua_getglobal(L, "Run");

		if (lua_isfunction(L, -1)) {
			for (int i = 0; i < 8; i++) {
				if (sTiles[i] != nullptr) {
					lua_pushnumber(L, sTiles[i]->state);
					lua_pushnumber(L, sTiles[i]->heat);
				}else{
					lua_pushnumber(L, 0);
					lua_pushnumber(L, 0);
				}
			}

			lua_pushnumber(L, t.state);
			lua_pushnumber(L, t.heat);
			lua_pushnumber(L, 255);
			lua_pushnumber(L, 255);
			lua_pushnumber(L, 255);

			checkVM(L, lua_pcall(L, 21, 5, 0));
			t.new_state = lua_tointeger(L, -1);
			t.new_heat  = lua_tointeger(L, -2);
			t.color.r   = (int)lua_tointeger(L, -3);
			t.color.g   = (int)lua_tointeger(L, -4);
			t.color.b   = (int)lua_tointeger(L, -5);
			lua_pop(L, 5);
		}
	}

	void deInitVM() {
		lua_close(L);
	}
}