#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class tile {
public:
	sf::Color color;
	std::string lua_path;
	int type, heat, state;
	int new_type, new_heat, new_state, pos_x, pos_y;

	tile();
	tile(const int type_, const int pos_x_, const int pos_y_);
	tile(const int type_, const int heat_, const int state_, const int pos_x_, const int pos_y_);

	void setLuaPath(const std::string& path);

	void lateUpdateTile();
	void updateTile();
};