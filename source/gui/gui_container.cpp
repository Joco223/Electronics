#include "gui_container.h"

guiContainer::guiContainer()
						:
						start_x(0),
						start_y(0),
						width(0),
						height(0),
						element_width(0),
						element_height(0),
						element_spacing(0),
						current_scroll(0),
						min_scroll(0),
						max_scroll(0),
						vertical(false),
						visible(false),
						name("") {}

guiContainer::guiContainer(const int start_x_, const int start_y_, const int width_, const int height_, const std::string& name_) 
						:
						start_x(start_x_),
						start_y(start_y_),
						width(width_),
						height(height_),
						name(name_),
						element_width(0),
						element_height(0),
						element_spacing(0),
						current_scroll(0),
						min_scroll(0),
						max_scroll(0),
						vertical(false),
						visible(false) {}

void guiContainer::registerElement(const std::string& name, const std::string& text) {
	gui_elements.push_back({name, text});
	current_scroll = 0;
	if (vertical) {
		max_scroll = (element_height + element_spacing) * gui_elements.size();
	}else{
		max_scroll = (element_width + element_spacing) * gui_elements.size();
	}
}

void guiContainer::scroll(const int amount) {
	if (amount > 0) {
		if (current_scroll + amount > max_scroll) {
			current_scroll = max_scroll;
		}else{
			current_scroll += amount;
		}
	}else{
		if (current_scroll + amount < min_scroll) {
			current_scroll = 0;
		}else{
			current_scroll += amount;
		}
	}
}

void guiContainer::setCorrectTextSize(const guiStyle& style) {
	int adjusted_height = element_height + style.border_thickness*2 - style.padding*2;
	int adjusted_width  = element_width  + style.border_thickness*2 - style.padding*2;

	text.setCharacterSize(static_cast<unsigned int>(adjusted_height));

	sf::FloatRect bounds = text.getLocalBounds();

	//text.setScale(sf::Vector2f(1, adjusted_height/bounds.height));
	text.setOrigin(sf::Vector2f(bounds.width/2, bounds.height/2));
}

void guiContainer::drawGuiContainer(sf::RenderWindow& window, const guiStyle style) {
	if (visible) {
		text.setFont(style.font);
		containerRect.setPosition(sf::Vector2f(start_x, start_y));
		containerRect.setSize(sf::Vector2f(width, height));
		containerRect.setFillColor(style.container_color);
		window.draw(containerRect);

		elementRect.setOutlineThickness(style.border_thickness);
		elementRect.setOutlineColor(style.border_color);
		
		if (vertical) {
			//Container title
			containerTitleRect.setPosition(sf::Vector2f(start_x, start_y));
			containerTitleRect.setSize(sf::Vector2f(width, element_height));
			containerTitleRect.setFillColor(style.container_color);
			containerTitleRect.setOutlineThickness(style.border_thickness);
			containerTitleRect.setOutlineColor(style.border_color);
			window.draw(containerTitleRect);

			text.setString(name);
			setCorrectTextSize(style);
			text.setPosition(sf::Vector2f(start_x - style.padding/2 + element_width/2, start_y - style.border_thickness*2 + style.padding*2));
			text.setFillColor(style.font_color);
			window.draw(text);

			int y_offset = element_height;
			elementRect.setSize(sf::Vector2f(width, element_height));

			for (auto element : gui_elements) {
				int element_pos_y = start_y + y_offset - current_scroll;
				if (element_pos_y + element_height + element_spacing > start_y && element_pos_y < start_y + height) {
					elementRect.setPosition(sf::Vector2f(start_x, element_pos_y));
					
					switch (element.state) {
						case deactivated: elementRect.setFillColor(style.background_color); break;
						case highlighted: elementRect.setFillColor(style.highlight_color); break;
						case activated:   elementRect.setFillColor(style.activated_color); break;
					}

					window.draw(elementRect);

					text.setString(element.text);
					setCorrectTextSize(style);
					text.setPosition(sf::Vector2f(start_x - style.padding/2 + element_width/2, element_pos_y - style.border_thickness*2 + style.padding*2));
					text.setFillColor(style.font_color);
					window.draw(text);
				}
				y_offset += element_height + element_spacing;
			}
		}else{
			int x_offset = 0;
			elementRect.setSize(sf::Vector2f(element_width, element_height));

			for (auto element : gui_elements) {
				int element_pos_x = start_x + x_offset - current_scroll;
				if (element_pos_x + element_width + element_spacing > start_x && element_pos_x < start_x + width) {
					elementRect.setPosition(sf::Vector2f(element_pos_x, start_y));

					switch (element.state) {
						case deactivated: elementRect.setFillColor(style.background_color); break;
						case highlighted: elementRect.setFillColor(style.highlight_color); break;
						case activated:   elementRect.setFillColor(style.activated_color); break;
					}

					window.draw(elementRect);

					text.setString(element.text);
					setCorrectTextSize(style);
					text.setPosition(sf::Vector2f(element_pos_x - style.padding/2 + element_width/2, start_y - style.border_thickness*2 + style.padding*2));
					text.setFillColor(style.font_color);
					window.draw(text);
				}
				x_offset += element_width + element_spacing;
			}
		}
	}
}

bool guiContainer::checkEvent(std::vector<guiEvent>& gui_events, const sf::Event& event) {
	sf::IntRect containerTestRect;
	containerTestRect.top = start_y;
	containerTestRect.left = start_x;
	containerTestRect.width = width;
	containerTestRect.height = height;

	sf::IntRect elementTestRect;

	int pos_y = start_y;
	int pos_x = start_x;

	elementTestRect.top = pos_y;
	elementTestRect.left = pos_x;
	elementTestRect.height = element_height;

	if (event.type != sf::Event::MouseWheelScrolled) {
		if (containerTestRect.contains(event.mouseButton.x, event.mouseButton.y) || containerTestRect.contains(event.mouseMove.x, event.mouseMove.y)) {
			for (int i = 0; i < gui_elements.size(); i++) {
				if (vertical) {
					pos_y = start_y + element_height + i*(element_height + element_spacing) - current_scroll;
					
					elementTestRect.top = pos_y;
					elementTestRect.width = width;	
					
					if (elementTestRect.contains(event.mouseButton.x, event.mouseButton.y) || elementTestRect.contains(event.mouseMove.x, event.mouseMove.y)) {
						if (event.type == sf::Event::MouseButtonPressed) {
							gui_events.push_back({name, gui_elements[i].name, event.mouseButton.button, 0});
						}else if (event.type == sf::Event::MouseMoved) {
							gui_events.push_back({name, gui_elements[i].name, mouseOver, 0});
						}
						return true;
					}
				}else{
					pos_x = start_x + i*(element_width + element_spacing) - current_scroll;
					elementTestRect.left = pos_x;
					elementTestRect.width = element_width;
					
					if (elementTestRect.contains(event.mouseButton.x, event.mouseButton.y) || elementTestRect.contains(event.mouseMove.x, event.mouseMove.y)) {
						if (event.type == sf::Event::MouseButtonPressed) {
							gui_events.push_back({name, gui_elements[i].name, leftClick, event.mouseButton.button});
						}else if (event.type == sf::Event::MouseMoved) {
							gui_events.push_back({name, gui_elements[i].name, mouseOver, 0});
						}
						return true;
					}
				}
			}
			return false;
		}else{
			return false;
		}
	}else{
		if (containerTestRect.contains(event.mouseWheelScroll.x, event.mouseWheelScroll.y)) {
			for (int i = 0; i < gui_elements.size(); i++) {
				if (vertical) {
					pos_y = start_y + element_height + i*(element_height + element_spacing) - current_scroll;
					elementTestRect.top = pos_y;
					elementTestRect.width = width;

					if (elementTestRect.contains(event.mouseWheelScroll.x, event.mouseWheelScroll.y)) {
						gui_events.push_back({name, gui_elements[i].name, mouseScroll, (int)event.mouseWheelScroll.delta});
						return true;
					}
				}else{
					pos_x = start_x + i*(element_width + element_spacing) - current_scroll;
					elementTestRect.left = pos_x;
					elementTestRect.width = element_width;

					if (elementTestRect.contains(event.mouseWheel.x, event.mouseWheel.y)) {
						gui_events.push_back({name, gui_elements[i].name, mouseScroll, (int)event.mouseWheelScroll.delta});
						return true;
					}
				}
			}
			return false;
		}else{
			return false;
		}
	}
}

guiElement* guiContainer::getElement(const std::string& name) {
	for (int i = 0; i < gui_elements.size(); i++) {
		if (gui_elements[i].name == name) {
			return &gui_elements[i];
		}
	}
	return nullptr;
}