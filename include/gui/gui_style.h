#pragma once

#include <SFML/Graphics.hpp>

class guiStyle {
public:
	sf::Color background_color, highlight_color, activated_color, border_color, font_color, container_color;
	sf::Font font;
	int border_thickness, padding;

	guiStyle() : border_thickness(0), padding(0) {};

	void setBackgroundColor(const sf::Color color) { background_color = color; };
	void setHighlightColor(const sf::Color color) { highlight_color = color; };
	void setActivatedColor(const sf::Color color) { activated_color = color; };
	void setBorderColor(const sf::Color color) { border_color = color; };
	void setFontColor(const sf::Color color) { font_color = color; };
	void setContainerColor(const sf::Color color) { container_color = color; }

	void setFont(const sf::Font font_) { font = font_; };
	
	void setBorderThickness(const int amount) { border_thickness = amount; };
	void setPadding(const int amount) { padding = amount; };
};