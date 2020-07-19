#include "drawer.h"

namespace drawer {

	constexpr int tile_pixel_size = 24;

	sf::RectangleShape chunkRect;
	sf::RectangleShape chunkDebugRect;
	sf::RectangleShape tileRect;

	void initDrawer() {
		tileRect.setSize(sf::Vector2f(tile_pixel_size, tile_pixel_size));

		chunkRect.setFillColor(sf::Color(20, 20, 20, 255));

		chunkDebugRect.setOutlineThickness(-2);
		chunkDebugRect.setOutlineColor(sf::Color(255, 0, 0, 255));
		chunkDebugRect.setFillColor(sf::Color(0, 0, 0, 0));
	}

	void drawChunk(sf::RenderWindow& window, chunk& chunk, const int window_width, const int window_height) {
		//Vertical lines
		chunkRect.setSize(sf::Vector2f(2, chunk.screen_size));

		for (int x = 0; x <= chunk.size; x++) {
			sf::Vector2f position(chunk.pos_x*chunk.screen_size + window_width/2 + x*tile_pixel_size,
			                      chunk.pos_y*chunk.screen_size + window_height/2);

			chunkRect.setPosition(position);
			window.draw(chunkRect);
		}

		//Horizontal lines
		chunkRect.setSize(sf::Vector2f(chunk.screen_size, 2));
		
		for (int y = 0; y <= chunk.size; y++) {
			sf::Vector2f position(chunk.pos_x*chunk.screen_size + window_width/2,
			                      chunk.pos_y*chunk.screen_size + window_height/2 + y*tile_pixel_size);

			chunkRect.setPosition(position);
			window.draw(chunkRect);
		}
	}

	void drawChunkDebug(sf::RenderWindow& window, chunk& chunk, const int window_width, const int window_height) {
		sf::Vector2f position(chunk.pos_x*chunk.screen_size + window_width/2,
												chunk.pos_y*chunk.screen_size + window_height/2);

		chunkDebugRect.setSize(sf::Vector2f(chunk.screen_size, chunk.screen_size));
		chunkDebugRect.setPosition(position);
		window.draw(chunkDebugRect);
	}

	void drawPlayingField(sf::RenderWindow& window, sf::View& camera, playingField& playing_field, const int window_width, const int window_height, const float scale) {
		std::vector<chunk*> visibleChunks = playing_field.getVisibleChunks(camera, window_width, window_height, scale);

		for (int i = 0; i < visibleChunks.size(); i++) {
			for (int j = 0; j < visibleChunks[i]->tiles.size(); j++) {
				drawTile(window, visibleChunks[i]->tiles[j], visibleChunks[i], window_width, window_height);
			}

			drawChunk(window, *visibleChunks[i], window_width, window_height);
		}
	}

	void drawPlayingFieldDebug(sf::RenderWindow& window, sf::View& camera, playingField& playing_field, const int window_width, const int window_height, const float scale) {
		std::vector<chunk*> visibleChunks = playing_field.getVisibleChunks(camera, window_width, window_height, scale);

		for (int i = 0; i < visibleChunks.size(); i++) {
			drawChunkDebug(window, *visibleChunks[i], window_width, window_height);
		}
	}

	void drawTile(sf::RenderWindow& window, tile& t, chunk* c, const int window_width, const int window_height) {
		sf::Vector2f position(c->pos_x*c->screen_size + t.pos_x*tile_pixel_size + window_width/2,
													c->pos_y*c->screen_size + t.pos_y*tile_pixel_size + window_height/2);

		tileRect.setFillColor(t.color);
		tileRect.setPosition(position);
		window.draw(tileRect);
	}
}