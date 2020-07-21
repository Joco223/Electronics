#include "tile.h"

tile::tile() : type(0), heat(273), state(0), pos_x(0), pos_y(0), new_type(0), new_heat(0), new_state(0), color(sf::Color(0, 0, 0, 255)), lua_index(-1), lua_path(""), physics_state(-1), new_physics_state(-1), liquid_direction(1), new_color(sf::Color(0, 0, 0, 255)) {}

tile::tile(const int type_, const int pos_x_, const int pos_y_)
    : type(type_), heat(273), state(0), pos_x(pos_x_), pos_y(pos_y_), new_type(type_), new_heat(273), new_state(0), color(sf::Color(0, 0, 0, 255)), lua_index(-1), lua_path(""), physics_state(-1), new_physics_state(-1), liquid_direction(1), new_color(sf::Color(0, 0, 0, 255)) {}

tile::tile(const int type_, const int heat_, const int state_, const int pos_x_, const int pos_y_)
    : type(type_), heat(heat_), state(state_), pos_x(pos_x_), pos_y(pos_y_), new_type(type_), new_heat(heat_), new_state(state_), color(sf::Color(0, 0, 0, 255)), lua_index(-1), lua_path(""), physics_state(-1), new_physics_state(-1), liquid_direction(1), new_color(sf::Color(0, 0, 0, 255)) {}

void tile::setLuaPath(const std::string& path) { lua_path = path; }

void tile::lateUpdateTile() {
	type = new_type;
	heat = new_heat;
	state = new_state;
	physics_state = new_physics_state;
	liquid_direction = new_liquid_direction;
	color = new_color;
}