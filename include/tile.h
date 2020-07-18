#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class tile {
private:
	int type, heat, pos_x, pos_y;
public:
	tile();
	tile(const int type_, const int pos_x_, const int pos_y_);
	tile(const int type_, const int heat_, const int pos_x_, const int pos_y_);

	void updateTile();
};