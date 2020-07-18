#include "drawer.h"

namespace drawer {
	sf::RectangleShape chunkDebugRect;

	void init_drawer() {
		chunkDebugRect.setOutlineThickness(5);
		chunkDebugRect.setOutlineColor(sf::Color(20, 20, 20, 255));
		chunkDebugRect.setFillColor(sf::Color(0, 0, 0, 0));
	}

	void drawChunkDebug(sf::RenderWindow& window, sf::View& camera, chunk& chunk, const int window_width, const int window_height) {
		int chunkScreenSize = chunk.size*24; //24 is standard tile pixel size

		sf::Vector2f position(chunk.pos_x*chunkScreenSize + window_width/2,
												chunk.pos_y*chunkScreenSize + window_height/2);

		chunkDebugRect.setSize(sf::Vector2f(chunkScreenSize, chunkScreenSize));
		chunkDebugRect.setPosition(position);
		window.draw(chunkDebugRect);
	}

	void drawPlayingFieldDebug(sf::RenderWindow& window, sf::View& camera, playingField& playing_field, const int window_width, const int window_height) {
		std::vector<chunk*> visibleChunks = playing_field.getVisibleChunks(camera, window_width, window_height);

		std::cout << visibleChunks.size() << '\n';

		for (int i = 0; i < visibleChunks.size(); i++) {
			drawChunkDebug(window, camera, *visibleChunks[i], window_width, window_height);
		}
	}
}