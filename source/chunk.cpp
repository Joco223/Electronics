#include "chunk.h"

chunk::chunk() : pos_x(0), pos_y(0), size(0), screen_size(0) {}

chunk::chunk(const int pos_x_, const int pos_y_, const int size_)
		 : pos_x(pos_x_), pos_y(pos_y_), size(size_) {
			  screen_size = size*24; //24 is tile pixel size
			  for (int y = 0; y < size; y++) {
				  for (int x = 0; x < size; x++) {
					  tile tmp(0, x, y);
						tmp.type = -1;
						tmp.new_type = -1;
					  tiles.push_back(tmp);
				  }
			  }
		  }

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

void chunk::generateSTilesCached(std::array<chunk*, 8>& sChunks) {
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			std::array<tile*, 8> sTiles = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

			if (y == 0) {
				if (x == 0) {
					if (sChunks[topLeft] != nullptr) sTiles[topLeft]    = &sChunks[topLeft]->tiles[(size - 1) + (size - 1) * size];  //Top left tile		
					if (sChunks[left]    != nullptr)  {
						sTiles[left]       = &sChunks[left]->tiles[(size - 1) +          y * size]; //Left tile
						sTiles[bottomLeft] = &sChunks[left]->tiles[(size - 1) + (   y + 1) * size]; //Bottom left tile
					} 
					if (sChunks[top]     != nullptr) sTiles[topRight]   = &sChunks[top]->tiles[(x + 1)    + (size - 1) * size];  //Top right tile
					sTiles[right]         = &tiles[(x + 1) +       y * size];                                                    //Right tile
					sTiles[bottomRight]   = &tiles[(x + 1) + (y + 1) * size];                                                    //Botom right tile
				}else if (x == size-1) {
					if (sChunks[top]      != nullptr) sTiles[topLeft]     = &sChunks[top]->tiles[(x - 1) + (size - 1) * size]; //Top left tile
					sTiles[left]                                          = &tiles[(x - 1) +          y * size];               //Left tile
					sTiles[bottomLeft]                                    = &tiles[(x - 1) +    (y + 1) * size];               //Bottom left tile
					if (sChunks[topRight] != nullptr) sTiles[topRight]    = &sChunks[topRight]->tiles[(size - 1) * size];      //Top right tile
					if (sChunks[right]    != nullptr) {
						sTiles[right]       = &sChunks[right]->tiles[0];    //Right tile
					  sTiles[bottomRight] = &sChunks[right]->tiles[size]; //Bottom right tile
					}                      
				}else{
					if (sChunks[top] != nullptr) {
						sTiles[topLeft] = &sChunks[top]->tiles[(x - 1) + (size - 1) * size];  //Top left tile
						sTiles[topRight] = &sChunks[top]->tiles[(x + 1) + (size - 1) * size]; //Top right tile
					} 
					sTiles[left] = &tiles[(x - 1) + y * size];                                                         //Left tile
					sTiles[bottomLeft] = &tiles[(x - 1) + (y + 1) * size];                                             //Bottom left tile
					
					sTiles[right] = &tiles[(x + 1) + y * size];                                                        //Right tile
					sTiles[bottomRight] = &tiles[(x + 1) + (y + 1) * size];                                            //Bottom right tile
				}
	
				if (sChunks[top] != nullptr) sTiles[top] = &sChunks[top]->tiles[x          + (size - 1) * size]; //Top tile
				sTiles[bottom] = &tiles[x + (y + 1) * size]; //Bottom tile
			}else if (y == size - 1) {
				if (x == 0) {
					if (sChunks[left] != nullptr) {
						sTiles[topLeft] = &sChunks[left]->tiles[(size - 1) + (y - 1) * size]; //Top left tile
						sTiles[left]    = &sChunks[left]->tiles[(size - 1) +       y * size]; //Left tile
					}
					if (sChunks[bottomLeft] != nullptr) sTiles[bottomLeft] = &sChunks[bottomLeft]->tiles[size - 1];     //Bottom left tile
					sTiles[topRight] = &tiles[(x + 1) + (y - 1) * size];                                                //Top right tile
					sTiles[right]    = &tiles[(x + 1) +       y * size];                                                //Right tile
					if (sChunks[bottom] != nullptr) sTiles[bottomRight] = &sChunks[bottom]->tiles[(x + 1)];             //Bottom right tile
				}else if (x == size - 1) {
					sTiles[topLeft] = &tiles[(x - 1) + (y - 1) * size];                                                //Top left tile
					sTiles[left]    = &tiles[(x - 1) +       y * size];                                                //Left tile
					if (sChunks[bottom]      != nullptr) sTiles[bottomLeft]  = &sChunks[bottom]->tiles[(x - 1)];       //Bottom left tile
					if (sChunks[right]       != nullptr) {
						sTiles[topRight]    = &sChunks[right]->tiles[(y - 1) * size]; //Top right tile
						sTiles[right]       = &sChunks[right]->tiles[y * size];       //Right tile
					}
					if (sChunks[bottomRight] != nullptr) sTiles[bottomRight] = &sChunks[bottomRight]->tiles[0];        //Bottom right tile
				}else{
					sTiles[topLeft] = &tiles[(x - 1) + (y - 1) * size];                                                //Top left tile
					sTiles[left]    = &tiles[(x - 1) +       y * size];                                                //Left tile
					sTiles[topRight] = &tiles[(x + 1) + (y - 1) * size];                                               //Top right tile
					sTiles[right]    = &tiles[(x + 1) +       y * size];                                               //Right tile
					if (sChunks[bottom] != nullptr) {
						sTiles[bottomLeft] = &sChunks[bottom]->tiles[x - 1]; //Bottom left tile
						sTiles[bottomRight] = &sChunks[bottom]->tiles[x + 1];
					}
				}
				sTiles[top] = &tiles[x + (y - 1) * size];                                    //Top tile
				if (sChunks[bottom] != nullptr) sTiles[bottom] = &sChunks[bottom]->tiles[x]; //Bottom tile
			}else{
				if (x == 0) {
					sTiles[top]         = &tiles[      x + (y - 1) * size]; //Top tile
					sTiles[topRight]    = &tiles[(x + 1) + (y - 1) * size]; //Top right tile
					sTiles[right]       = &tiles[(x + 1) +       y * size]; //Right tile
					sTiles[bottomRight] = &tiles[(x + 1) + (y + 1) * size]; //Bottom right tile
					sTiles[bottom]      = &tiles[      x + (y + 1) * size]; //Bottom tile
					if (sChunks[left] != nullptr) {
						sTiles[topLeft]    = &sChunks[left]->tiles[(size - 1) + (y - 1) * size]; //Top left tile
						sTiles[left]       = &sChunks[left]->tiles[(size - 1) + y * size];       //Left tile
						sTiles[bottomLeft] = &sChunks[left]->tiles[(size - 1) + (y + 1) * size]; //Bottom left tile
					}
				}else if (x == size - 1) {
					sTiles[topLeft]     = &tiles[(x - 1) + (y - 1) * size]; //Top left tile
					sTiles[top]         = &tiles[      x + (y - 1) * size]; //Top tile
					if (sChunks[right] != nullptr) {
						sTiles[topRight]    = &sChunks[right]->tiles[(y - 1) * size]; //Top right tile
						sTiles[right]       = &sChunks[right]->tiles[y * size];       //Right tile
						sTiles[bottomRight] = &sChunks[right]->tiles[(y + 1) * size]; //Bottom right
					}
					sTiles[left]        = &tiles[(x - 1) +       y * size]; //Left tile
					sTiles[bottomLeft]  = &tiles[(x - 1) + (y + 1) * size]; //Bottom left tile
					sTiles[bottom]      = &tiles[      x + (y + 1) * size]; //Bottom tile
				}else{
					sTiles[topLeft]     = &tiles[(x - 1) + (y - 1) * size]; //Top left tile
					sTiles[top]         = &tiles[      x + (y - 1) * size]; //Top tile
					sTiles[topRight]    = &tiles[(x + 1) + (y - 1) * size]; //Top right tile
					sTiles[left]        = &tiles[(x - 1) +       y * size]; //Left tile
					sTiles[right]       = &tiles[(x + 1) +       y * size]; //Right tile
					sTiles[bottomLeft]  = &tiles[(x - 1) + (y + 1) * size]; //Bottom left tile
					sTiles[bottom]      = &tiles[      x + (y + 1) * size]; //Bottom tile
					sTiles[bottomRight] = &tiles[(x + 1) + (y + 1) * size]; //Bottom right tile
				}
			}

			sTilesCached.push_back(sTiles);
		}
	}
}

void chunk::updateTiles(std::array<chunk*, 8>& sChunks) {
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			luaVM::updateTile(tiles[x + y * size], sTilesCached[x + y * size]);
		}
	}
}