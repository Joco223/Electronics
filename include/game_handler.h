#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "playing_field.h"
#include "tile.h"

namespace gameHandler {
	struct tileType {
		std::string name, script_path;
		int internal_type;
	};

	std::vector<tileType> tile_types;
	tileType* currentSelectedType = nullptr;

	void addTileType(const std::string& name, const std::string& script_path) {
		tile_types.push_back({name, script_path, (int)tile_types.size()});
	}

	void clearTileType() { currentSelectedType = nullptr; }

	void selectTileType(const std::string& name) {
		for (auto& type : tile_types) {
			if (type.name == name) {
				currentSelectedType = &type;
				return;
			}
		}
		currentSelectedType = nullptr;
	}

	void setTile(tile& t) {
		t.new_state = -1;
		t.new_heat = 273;
		t.lua_index = -1;

		if (currentSelectedType != nullptr) {
			t.new_state = 0;
			t.new_type = currentSelectedType->internal_type;
			t.lua_path = currentSelectedType->script_path;
		}else{
			t.lua_path = "";
			t.new_type = -1;
		}
	}

	void handleClick(const int button, tile& t) {
		if (button == 0) {
			if (currentSelectedType != nullptr) {
				if (currentSelectedType->name == "spark") {
					t.new_state = 2;
				}else{
					setTile(t);
				}
			}else{
				setTile(t);
			}			
		}else{
			std::string tmp = currentSelectedType->name;
			currentSelectedType = nullptr;
			setTile(t);
			selectTileType(tmp);
		}
		t.lateUpdateTile();
	}
}