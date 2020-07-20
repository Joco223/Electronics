#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "gui_style.h"
#include "gui_event.h"

enum elementStates {
	deactivated,
	highlighted,
	activated
};

struct guiElement {
	std::string name, text;
	int state = deactivated;
};

class guiContainer {
private:
	std::string name;
	int start_x, start_y, width, height, element_width, element_height, element_spacing, current_scroll, min_scroll, max_scroll;
	bool vertical, visible;
	sf::RectangleShape containerRect;
	sf::RectangleShape elementRect;
	sf::RectangleShape containerTitleRect;
	sf::Text text;

	void setCorrectTextSize(const guiStyle& style);

public:
	std::vector<guiElement> gui_elements;
	guiContainer();
	guiContainer(const int start_x_, const int start_y_, const int width_, const int height_, const std::string& name_);

	void setElementSpacing(const int amount) { element_spacing = amount; };
	void setIsVertical(const bool vertical_) { vertical = vertical_; };
	void setElementWidth(const int amount) { element_width = amount; };
	void setElementHeight(const int amount) { element_height = amount; };
	
	std::string getName() { return name; };

	void setVisibility(const bool visibility) { visible = visibility; };
	bool isVisible() { return visible; }

	void drawGuiContainer(sf::RenderWindow& window, const guiStyle style);
	void registerElement(const std::string& name, const std::string& text);
	void scroll(const int amount);
	bool checkEvent(std::vector<guiEvent>& gui_events, const sf::Event& event);

	guiElement* getElement(const std::string& name);
};