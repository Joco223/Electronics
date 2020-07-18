#include "playing_field.h"

void playingField::generateChunksSquare(const int width, const int height, const int chunk_size) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			chunk tmp(x, y, chunk_size);
			chunks.push_back(tmp);
		}
	}
}

std::vector<chunk*> playingField::getVisibleChunks(sf::View& camera, const int window_width, const int window_height) {
	std::vector<chunk*> visibleChunks;

	for (auto& c : chunks) {
		int chunkScreenSize = c.size*24; //24 Is default tile size in pixels
		if ((c.pos_x+1)*chunkScreenSize - camera.getCenter().x + window_width/2 > -window_width/2) { //Left screen edge
			if (c.pos_x*chunkScreenSize - camera.getCenter().x + window_width/2 < window_width/2) { //Right screen edge
				if ((c.pos_y+1)*chunkScreenSize - camera.getCenter().y + window_height/2 > -window_height/2) { //Bottom screen edge
					if (c.pos_y*chunkScreenSize - camera.getCenter().y + window_height/2 < window_height/2) { //Top screen edge
						visibleChunks.push_back(&c);
					}
				}
			}
		}
	}

	return visibleChunks;
}