#include "tile_physics.h"

namespace tilePhysics {

	enum sides {
		topLeft,
		top,
		topRight,
		left,
		right,
		bottomLeft,
		bottom,
		bottomRight
	};

	void swapTiles(tile& t1, tile& t2) {
		tile tmp = t2;

		t2.new_type = t1.type;
		t2.new_heat = t1.heat;
		t2.new_state = t1.state;
		t2.new_physics_state = t1.physics_state;
		t2.new_liquid_direction = t1.liquid_direction;
		t2.lua_index = t1.lua_index;
		t2.lua_path = t1.lua_path;
		t2.new_color = t1.color;

		t1.new_type = tmp.type;
		t1.new_heat = tmp.heat;
		t1.new_state = tmp.state;
		t1.new_physics_state = tmp.physics_state;
		t1.lua_index = tmp.lua_index;
		t1.lua_path = tmp.lua_path;
		t1.new_color = tmp.color;
		t1.new_liquid_direction = tmp.liquid_direction;
	}

	void updateTilePhysicsLiquids(tile& t, std::array<tile*, 8> sTiles) { 
		if (t.physics_state == liquid) {
			if (sTiles[bottom] != nullptr) {
				if (sTiles[bottom]->type == -1 && sTiles[bottom]->new_type == -1) {
					swapTiles(t, *sTiles[bottom]);
					return;
				}
			}

			if (sTiles[bottomLeft] != nullptr) {
				if (sTiles[bottomLeft]->type == -1 && sTiles[bottomLeft]->new_type == -1) {
					swapTiles(t, *sTiles[bottomLeft]);
					return;
				}
			}
			if (sTiles[bottomRight] != nullptr) {
				if (sTiles[bottomRight]->type == -1 && sTiles[bottomRight]->new_type == -1) {
					swapTiles(t, *sTiles[bottomRight]);
					return;
				}
			}
			if (t.liquid_direction == 1) {
				if (sTiles[right] != nullptr) {
					if (sTiles[right]->type == -1 && sTiles[right]->new_type == -1) {
						swapTiles(t, *sTiles[right]);
						return;
					}else{
						t.new_liquid_direction = 0;
						return;
					}
				}else{
					t.new_liquid_direction = 0;
					return;
				}
			}else{			
				if (sTiles[left] != nullptr) {
					if (sTiles[left]->type == -1 && sTiles[left]->new_type == -1) {
						swapTiles(t, *sTiles[left]);
						return;
					}else{
						t.new_liquid_direction = 1;
						return;
					}
				}else{
					t.new_liquid_direction = 1;
					return;
				}
			}
		}
	}

	void updateTilePhysicsDusts(tile& t, std::array<tile*, 8> sTiles) {
		if (t.physics_state == dust) {
			if (sTiles[bottom] != nullptr) {
				if ((sTiles[bottom]->type == -1 && sTiles[bottom]->new_type == -1) || (sTiles[bottom]->physics_state == liquid && sTiles[bottom]->new_physics_state == liquid)) {
					swapTiles(t, *sTiles[bottom]);
					return;
				}
			}
			
			if (sTiles[bottomLeft] != nullptr) {
				if ((sTiles[bottomLeft]->type == -1 && sTiles[bottomLeft]->new_type == -1) || (sTiles[bottomLeft]->physics_state == liquid && sTiles[bottomLeft]->new_physics_state == liquid)) {
					swapTiles(t, *sTiles[bottomLeft]);
					return;
				}
			}
			if (sTiles[bottomRight] != nullptr) {
				if ((sTiles[bottomRight]->type == -1 && sTiles[bottomRight]->new_type == -1) || (sTiles[bottomRight]->physics_state == liquid && sTiles[bottomRight]->new_physics_state == liquid)) {
					swapTiles(t, *sTiles[bottomRight]);
					return;
				}
			}
		}
	}

	void updateTilePhysicsWetSolids(tile& t, std::array<tile*, 8> sTiles) {
		if (t.physics_state == wet_solid) {
			if (sTiles[bottom] != nullptr) {
				if ((sTiles[bottom]->type == -1 && sTiles[bottom]->new_type == -1) || (sTiles[bottom]->physics_state == liquid && sTiles[bottom]->new_physics_state != liquid)) {
					swapTiles(t, *sTiles[bottom]);
					return;
				}
			}
		}
	}
};