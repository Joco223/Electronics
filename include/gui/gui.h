#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "gui_container.h"
#include "gui_event.h"

class GUI {
public:
std::vector<guiContainer> containers;
	std::vector<guiEvent> events;

	GUI() {};

	void drawGUI(sf::RenderWindow& window, const guiStyle& style);
	guiContainer* getGuiContainer(const std::string& name);
	void registerContainer(const int start_x, const int start_y, const int width, const int height, const std::string& name);
	bool handleEvent(const sf::Event& event);
	void addEvent(const std::string& container, const std::string& element, const int event_type);
};