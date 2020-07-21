#include "lua_vm.h"

namespace luaVM {
	sol::state L;
	sol::table states;
	sol::table heats;
	sol::table types;

	void initVM() {
		L.open_libraries(sol::lib::base);

		states = L.create_table_with("TopLeft", 0, 
																 "Top", 0,
																 "TopRight", 0,
															   "Left", 0,
																 "Right", 0,
																 "BottomLeft", 0,
																 "Bottom", 0,
																 "BottomRight", 0);

		heats = L.create_table_with("TopLeft", 0, 
																"Top", 0,
																"TopRight", 0,
																"Left", 0,
																"Right", 0,
																"BottomLeft", 0,
																"Bottom", 0,
																"BottomRight", 0);
								
		types = L.create_table_with("TopLeft", 0, 
																"Top", 0,
																"TopRight", 0,
																"Left", 0,
																"Right", 0,
																"BottomLeft", 0,
																"Bottom", 0,
																"BottomRight", 0);
	}

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

	void loadArguments(std::array<tile*, 8>& sTiles) {
		if (sTiles[0] != nullptr) { states["TopLeft"]     = sTiles[0]->state; heats["TopLeft"]     = sTiles[0]->heat; types["TopLeft"]     = sTiles[0]->type; } else { states["TopLeft"]     = 0; heats["TopLeft"]     = 0; types["TopLeft"]     = 0; }
		if (sTiles[1] != nullptr) { states["Top"]         = sTiles[1]->state; heats["Top"]         = sTiles[1]->heat; types["Top"]         = sTiles[1]->type; } else { states["Top"]         = 0; heats["Top"]         = 0; types["Top"]         = 0; }
		if (sTiles[2] != nullptr) { states["TopRight"]    = sTiles[2]->state; heats["TopRight"]    = sTiles[2]->heat; types["TopRight"]    = sTiles[2]->type; } else { states["TopRight"]    = 0; heats["TopRight"]    = 0; types["TopRight"]    = 0; }
		if (sTiles[3] != nullptr) { states["Left"]        = sTiles[3]->state; heats["Left"]        = sTiles[3]->heat; types["Left"]        = sTiles[3]->type; } else { states["Left"]        = 0; heats["Left"]        = 0; types["Left"]        = 0; }
		if (sTiles[4] != nullptr) { states["Right"]       = sTiles[4]->state; heats["Right"]       = sTiles[4]->heat; types["Right"]       = sTiles[4]->type; } else { states["Right"]       = 0; heats["Right"]       = 0; types["Right"]       = 0; }
		if (sTiles[5] != nullptr) { states["BottomLeft"]  = sTiles[5]->state; heats["BottomLeft"]  = sTiles[5]->heat; types["BottomLeft"]  = sTiles[5]->type; } else { states["BottomLeft"]  = 0; heats["BottomLeft"]  = 0; types["BottomLeft"]  = 0; }
		if (sTiles[6] != nullptr) { states["Bottom"]      = sTiles[6]->state; heats["Bottom"]      = sTiles[6]->heat; types["Bottom"]      = sTiles[6]->type; } else { states["Bottom"]      = 0; heats["Bottom"]      = 0; types["Bottom"]      = 0; }
		if (sTiles[7] != nullptr) { states["BottomRight"] = sTiles[7]->state; heats["BottomRight"] = sTiles[7]->heat; types["BottomRight"] = sTiles[7]->type; } else { states["BottomRight"] = 0; heats["BottomRight"] = 0; types["BottomRight"] = 0; }
	}

	std::vector<int> arguments(16);

	void updateTile(tile& t, std::array<tile*, 8>& sTiles) {
		if (t.lua_path != "") {
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

			L.script(loadedFiles[t.lua_index]);
			loadArguments(sTiles);
			sol::tie(t.new_state, t.new_heat, t.new_color.r, t.new_color.g, t.new_color.b) = L["Run"](states, heats, types, t.state, t.heat, t.color.r, t.color.g, t.color.b);
		}
	}
}