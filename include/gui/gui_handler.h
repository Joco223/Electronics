#pragma once

#include <string>

#include "gui.h"
#include "gui_container.h"
#include "game_handler.h"

namespace guiHandler {
	GUI gui;
	guiStyle basicStyle;
	sf::Font font;

	void initGui(const int window_width, const int window_height) {
		font.loadFromFile("/usr/share/fonts/truetype/hack/Hack-Regular.ttf");

		basicStyle.setBackgroundColor(sf::Color(20, 20, 20, 255));
		basicStyle.setHighlightColor(sf::Color(40, 40, 40, 255));
		basicStyle.setActivatedColor(sf::Color(60, 60, 60, 255));
		basicStyle.setBorderColor(sf::Color(120, 120, 120, 255));
		basicStyle.setBorderThickness(-2);
		basicStyle.setFontColor(sf::Color(255, 255, 255, 255));
		basicStyle.setContainerColor(sf::Color(20, 20, 20, 150));
		basicStyle.setPadding(3);
		basicStyle.setFont(font);

		gui.registerContainer(0, window_height-30, window_width, 30, "Main bar");
		gui.getGuiContainer("Main bar")->setElementHeight(30);
		gui.getGuiContainer("Main bar")->setElementSpacing(1);
		gui.getGuiContainer("Main bar")->setElementWidth(100);
		gui.getGuiContainer("Main bar")->registerElement("tools", "Tools");
		gui.getGuiContainer("Main bar")->registerElement("tiles", "Tiles");
		gui.getGuiContainer("Main bar")->registerElement("save" , "Save");
		gui.getGuiContainer("Main bar")->registerElement("load" , "Load");
		gui.getGuiContainer("Main bar")->registerElement("pause", "Pause");
		gui.getGuiContainer("Main bar")->registerElement("grid" , "Grid");
		gui.getGuiContainer("Main bar")->registerElement("quit" , "Quit");
		gui.getGuiContainer("Main bar")->setVisibility(true);

		gui.registerContainer(0, window_height-30-300, 200, 300, "Tools");
		gui.getGuiContainer("Tools")->setElementHeight(30);
		gui.getGuiContainer("Tools")->setElementSpacing(1);
		gui.getGuiContainer("Tools")->setElementWidth(200);
		gui.getGuiContainer("Tools")->setIsVertical(true);
		gui.getGuiContainer("Tools")->registerElement("dot"   , "Dot");
		gui.getGuiContainer("Tools")->registerElement("line"  , "Line");
		gui.getGuiContainer("Tools")->registerElement("square", "Square");	

		gui.registerContainer(100, window_height-30-300, 200, 300, "Tiles");
		gui.getGuiContainer("Tiles")->setElementHeight(30);
		gui.getGuiContainer("Tiles")->setElementSpacing(1);
		gui.getGuiContainer("Tiles")->setElementWidth(200);
		gui.getGuiContainer("Tiles")->setIsVertical(true);
		gui.getGuiContainer("Tiles")->registerElement("metal", "Metal");
		gui.getGuiContainer("Tiles")->registerElement("spark", "Spark");
		gui.getGuiContainer("Tiles")->registerElement("stone", "Stone");
		gui.getGuiContainer("Tiles")->registerElement("dirt" , "Dirt");
		gui.getGuiContainer("Tiles")->registerElement("water", "Water");
		gui.getGuiContainer("Tiles")->registerElement("sand" , "Sand");
	}

	void toggleElement(const std::string& container, const std::string& element, bool& toggle) {
		if (gui.getGuiContainer(container)->getElement(element)->state == highlighted){
			gui.getGuiContainer(container)->getElement(element)->state = activated;
			toggle = true;
		}else{
			gui.getGuiContainer(container)->getElement(element)->state = highlighted;
			toggle = false;
		}	
	}

	void deactivateElements(const std::string& container, const std::string& exclude) {
		for (auto& i : gui.getGuiContainer(container)->gui_elements) {
			if (exclude != i.name) {
				i.state = deactivated;
			}
		}
	}

	bool processGuiEvents(bool& draw_grid, bool& is_paused) {
		bool throwaway;
		for (auto i : gui.events) {
			if (i.event_type == mouseOver) {
				if (i.container == "input_handler" && i.element == "screen") {
					for (auto& container : gui.containers) {
						for (auto& element : container.gui_elements) {
							if (element.state != activated) {
								element.state = deactivated;
							}
						}
					}
				}else{
					if (gui.getGuiContainer(i.container)->getElement(i.element)->state == deactivated) {
						gui.getGuiContainer(i.container)->getElement(i.element)->state = highlighted;
					}
					
					for (auto& container : gui.containers) {
						for (auto& element : container.gui_elements) {
							if (element.state != activated && element.name != i.element) {
								element.state = deactivated;
							}
						}
					}
				}
			}

			if (i.event_type == mouseScroll) {
				gui.getGuiContainer(i.container)->scroll(i.amount);
			}

			if (i.event_type == leftClick) {
				if (i.container == "Main bar") {
					if (i.element == "tools") {
						if (!gui.getGuiContainer("Tools")->isVisible()) {
							gui.getGuiContainer("Tools")->setVisibility(true);
						}else{
							gui.getGuiContainer("Tools")->setVisibility(false);
						}	
						gui.getGuiContainer("Tiles")->setVisibility(false);
					}else if (i.element == "tiles") {
						gui.getGuiContainer("Tools")->setVisibility(false);
						if (!gui.getGuiContainer("Tiles")->isVisible()) {
							gui.getGuiContainer("Tiles")->setVisibility(true);	
						}else{
							gui.getGuiContainer("Tiles")->setVisibility(false);
						}
					}else if (i.element == "pause") {
						toggleElement("Main bar", "pause", is_paused);
					}else if (i.element == "grid") {
						toggleElement("Main bar", "grid", draw_grid);
					}else if (i.element == "quit") {
						return true;
					}else{
						gui.getGuiContainer("Tools")->setVisibility(false);
						gui.getGuiContainer("Tiles")->setVisibility(false);
					}
				}else if (i.container == "Tiles") {
					gameHandler::selectTileType(i.element);
					toggleElement(i.container, i.element, throwaway);
					deactivateElements(i.container, i.element);
				}else if (i.container == "input_handler") {
					gui.getGuiContainer("Tools")->setVisibility(false);
					gui.getGuiContainer("Tiles")->setVisibility(false);
				}
			}
		}

		gui.events.clear();
		return false;
	}
};