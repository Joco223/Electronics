#include "playing_field.h"

void playingField::generateChunksSquare(const int width_, const int height_, const int chunk_size) {
	width = width_;
	height = height_;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			chunk tmp(x, y, chunk_size);
			chunks.emplace_back(tmp);
		}
	}
}

std::vector<chunk*> playingField::getVisibleChunks(sf::View& camera, const int window_width, const int window_height, const float scale) {
	std::vector<chunk*> visibleChunks;

	for (auto& c : chunks) {
		if ((c.pos_x+1)*c.screen_size - camera.getCenter().x + window_width/2 > -window_width/2*scale) {       //Left screen edge
			if (c.pos_x*c.screen_size - camera.getCenter().x + window_width/2 < window_width/2*scale) {          //Right screen edge
				if ((c.pos_y+1)*c.screen_size - camera.getCenter().y + window_height/2 > -window_height/2*scale) { //Bottom screen edge
					if (c.pos_y*c.screen_size - camera.getCenter().y + window_height/2 < window_height/2*scale) {    //Top screen edge
						visibleChunks.push_back(&c);
					}
				}
			}
		}
	}

	return visibleChunks;
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

void playingField::updateChunks() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			std::array<chunk*, 8> sChunks = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

			if (chunks.size() > 1) {
				if (y == 0) {
					if (x == 0) {
						sChunks[right]       = &chunks[(x + 1) + y * width];
						sChunks[bottomRight] = &chunks[(x + 1) + (y + 1) * width];
					}else if (x == width - 1) {
						sChunks[left]       = &chunks[(x - 1) + y * width];
						sChunks[bottomLeft] = &chunks[(x - 1) + (y + 1) * width];
					}else{
						sChunks[left]        = &chunks[(x - 1) + y * width];
						sChunks[bottomLeft]  = &chunks[(x - 1) + (y + 1) * width];
						sChunks[right]       = &chunks[(x + 1) + y * width];
						sChunks[bottomRight] = &chunks[(x + 1) + (y + 1) * width];
					}
					sChunks[bottom] = &chunks[x + (y + 1) * width];
				}else if (y == height - 1) {
					if (x == 0) {
						sChunks[topRight] = &chunks[(x + 1) + (y - 1) * width];
						sChunks[right]    = &chunks[(x + 1) + y * width];
					}else if (x == width -1) {
						sChunks[topLeft] = &chunks[(x - 1) + (y - 1) * width];
						sChunks[left]    = &chunks[(x - 1) + y * width];
					}else{
						sChunks[left]     = &chunks[(x - 1) + y * width];
						sChunks[topLeft]  = &chunks[(x - 1) + (y - 1) * width];
						sChunks[topRight] = &chunks[(x + 1) + (y - 1) * width];
						sChunks[right]    = &chunks[(x + 1) + y * width];
					}
					sChunks[top] = &chunks[x + (y - 1) * width];
				}else{
					if (x == 0) {
						sChunks[top]         = &chunks[x + (y - 1) * width];
						sChunks[topRight]    = &chunks[(x + 1) + (y - 1) * width];
						sChunks[right]       = &chunks[(x + 1) + y * width];
						sChunks[bottomRight] = &chunks[(x + 1) + (y + 1) * width];
						sChunks[bottom]      = &chunks[x + (y + 1) * width];
					}else if (x == width - 1) {
						sChunks[left]        = &chunks[(x - 1) + y * width];
						sChunks[topLeft]     = &chunks[(x - 1) + (y - 1) * width];
						sChunks[top]         = &chunks[x + (y - 1) * width];
						sChunks[bottom]      = &chunks[x + (y + 1) * width];
						sChunks[bottomLeft]  = &chunks[(x - 1) + (y + 1) * width];
					}else{
						sChunks[left]        = &chunks[(x - 1) + y * width];
						sChunks[topLeft]     = &chunks[(x - 1) + (y - 1) * width];
						sChunks[top]         = &chunks[x + (y - 1) * width];
						sChunks[topRight]    = &chunks[(x + 1) + (y - 1) * width];
						sChunks[right]       = &chunks[(x + 1) + y * width];
						sChunks[bottomRight] = &chunks[(x + 1) + (y + 1) * width];
						sChunks[bottom]      = &chunks[x + (y + 1) * width];
						sChunks[bottomLeft]  = &chunks[(x - 1) + (y + 1) * width];
					}
				}
			}

			chunks[x + y * width].updateTiles(sChunks);
		}
	}

	for (int i = 0; i < chunks.size(); i++) {
		for (int j = 0; j < chunks[i].tiles.size(); j++) {
			chunks[i].tiles[j].lateUpdateTile();
		}
	}
}