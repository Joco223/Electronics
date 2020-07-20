#pragma once

#include "gui.h"
#include "gui_container.h"

namespace guiHandler {
	GUI gui;
	guiStyle basicStyle;
	sf::Font font;

	void initGui(const int window_width, const int window_height) {
		font.loadFromFile("/usr/share/fonts/truetype/hack/Hack-Regular.ttf");

		basicStyle.setBackgroundColor(sf::Color(0, 4, 33, 255));
		basicStyle.setHighlightColor(sf::Color(0, 8, 64, 255));
		basicStyle.setActivatedColor(sf::Color(0, 36, 137, 255));
		basicStyle.setBorderColor(sf::Color(180, 180, 180, 255));
		basicStyle.setBorderThickness(-2);
		basicStyle.setFontColor(sf::Color(255, 255, 255, 255));
		basicStyle.setContainerColor(sf::Color(0, 3, 20, 255));
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
		gui.getGuiContainer("Main bar")->registerElement("quit" , "Quit");
		gui.getGuiContainer("Main bar")->registerElement("grid" , "Grid");
		gui.getGuiContainer("Main bar")->setVisibility(true);

		gui.registerContainer(0, window_height-30-300, 200, 300, "Tools");
		gui.getGuiContainer("Tools")->setElementHeight(30);
		gui.getGuiContainer("Tools")->setElementSpacing(1);
		gui.getGuiContainer("Tools")->setElementWidth(200);
		gui.getGuiContainer("Tools")->registerElement("dot"   , "Dot");
		gui.getGuiContainer("Tools")->registerElement("line"  , "Line");
		gui.getGuiContainer("Tools")->registerElement("square", "Square");
		gui.getGuiContainer("Tools")->setIsVertical(true);

		gui.registerContainer(100, window_height-30-300, 200, 300, "Tiles");
		gui.getGuiContainer("Tiles")->setElementHeight(30);
		gui.getGuiContainer("Tiles")->setElementSpacing(1);
		gui.getGuiContainer("Tiles")->setElementWidth(200);
		gui.getGuiContainer("Tiles")->registerElement("metal", "Metal");
		gui.getGuiContainer("Tiles")->registerElement("stone", "Stone");
		gui.getGuiContainer("Tiles")->registerElement("dirt" , "Dirt");
		gui.getGuiContainer("Tiles")->registerElement("water", "Water");
		gui.getGuiContainer("Tiles")->setIsVertical(true);
	}

	bool processGuiEvents() {
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
						if (gui.getGuiContainer("Main bar")->getElement("pause")->state == highlighted){
							gui.getGuiContainer("Main bar")->getElement("pause")->state = activated;
						}else{
							gui.getGuiContainer("Main bar")->getElement("pause")->state = deactivated;
						}			
					}else if (i.element == "quit") {
						return true;
					}else{
						gui.getGuiContainer("Tools")->setVisibility(false);
						gui.getGuiContainer("Tiles")->setVisibility(false);
					}
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