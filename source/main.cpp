#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

#include "input_handler.h"
#include "playing_field.h"
#include "drawer.h"
#include "lua_vm.h"

#include "gui/gui.h"
#include "gui/gui_container.h"
#include "gui/gui_style.h"

constexpr int width = 1280;
constexpr int height = 720;

int main(int argc, char** argv) {
	playingField playing_field;
	playing_field.generateChunksSquare(4, 4, 8);
	playing_field.generateSChunksCached();
	float scale = 1.0f;

	sf::ContextSettings settings;
 settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(width, height), "Electronics", sf::Style::Close, settings);
	window.setFramerateLimit(60);
	sf::View camera = window.getDefaultView();

	bool keyWasUpdated = false;

	drawer::initDrawer();

	auto start = std::chrono::high_resolution_clock::now();
	int frameCounter = 0;

	luaVM::initVM();

	//GUI stuff
	GUI gui;

	sf::Font font;
	font.loadFromFile("/usr/share/fonts/truetype/hack/Hack-Regular.ttf");

	guiStyle basicStyle;
	basicStyle.setBackgroundColor(sf::Color(0, 4, 33, 255));
	basicStyle.setHighlightColor(sf::Color(0, 8, 64, 255));
	basicStyle.setActivatedColor(sf::Color(0, 36, 137, 255));
	basicStyle.setBorderColor(sf::Color(180, 180, 180, 255));
	basicStyle.setBorderThickness(-2);
	basicStyle.setFontColor(sf::Color(255, 255, 255, 255));
	basicStyle.setContainerColor(sf::Color(0, 3, 20, 255));
	basicStyle.setPadding(3);
	basicStyle.setFont(font);

	gui.registerContainer(0, height-30, width, 30, "Main bar");
	gui.getGuiContainer("Main bar")->setElementHeight(30);
	gui.getGuiContainer("Main bar")->setElementSpacing(1);
	gui.getGuiContainer("Main bar")->setElementWidth(100);
	gui.getGuiContainer("Main bar")->registerElement("tools", "Tools");
	gui.getGuiContainer("Main bar")->registerElement("tiles", "Tiles");
	gui.getGuiContainer("Main bar")->registerElement("save" , "Save");
	gui.getGuiContainer("Main bar")->registerElement("load" , "Load");
	gui.getGuiContainer("Main bar")->registerElement("pause", "Pause");
	gui.getGuiContainer("Main bar")->registerElement("quit" , "Quit");
	gui.getGuiContainer("Main bar")->setVisibility(true);

	gui.registerContainer(0, height-30-300, 200, 300, "Tools");
	gui.getGuiContainer("Tools")->setElementHeight(30);
	gui.getGuiContainer("Tools")->setElementSpacing(1);
	gui.getGuiContainer("Tools")->setElementWidth(200);
	gui.getGuiContainer("Tools")->registerElement("dot"   , "Dot");
	gui.getGuiContainer("Tools")->registerElement("line"  , "Line");
	gui.getGuiContainer("Tools")->registerElement("square", "Square");
	gui.getGuiContainer("Tools")->setIsVertical(true);

	gui.registerContainer(100, height-30-300, 200, 300, "Tiles");
	gui.getGuiContainer("Tiles")->setElementHeight(30);
	gui.getGuiContainer("Tiles")->setElementSpacing(1);
	gui.getGuiContainer("Tiles")->setElementWidth(200);
	gui.getGuiContainer("Tiles")->registerElement("metal", "Metal");
	gui.getGuiContainer("Tiles")->registerElement("stone", "Stone");
	gui.getGuiContainer("Tiles")->registerElement("dirt" , "Dirt");
	gui.getGuiContainer("Tiles")->registerElement("water", "Water");
	gui.getGuiContainer("Tiles")->setIsVertical(true);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}else if (event.type == sf::Event::KeyPressed) {
				inputHandler::checkPressedKeys(event);
				keyWasUpdated = true;
			}else if (event.type == sf::Event::KeyReleased) {
				inputHandler::checkReleasedKeys(event);
				keyWasUpdated = true;
			}else if (event.type == sf::Event::MouseButtonPressed) {
				inputHandler::handleMouse(window, camera, event, &playing_field, &gui, width, height, scale);
			}else if (event.type == sf::Event::MouseWheelScrolled) {
				inputHandler::handleMouse(window, camera, event, &playing_field, &gui, width, height, scale);
			}else if (event.type == sf::Event::MouseMoved) {
				inputHandler::handleMouse(window, camera, event, &playing_field, &gui, width, height, scale);
			}
		}

		if (keyWasUpdated) {
			inputHandler::updateCamera(camera, 5, scale);
		}

		playing_field.updateChunks();

		for (auto i : gui.events) {
			if (i.event_type == mouseOver) {
				for (auto& container : gui.containers) {
					for (auto& element : container.gui_elements) {
						if (!(i.container == "input_handler" && i.element == "screen")) {
							if (i.container == "Main bar" && i.element == "pause") {
								if (gui.getGuiContainer("Main bar")->getElement("pause")->state == deactivated) {
									if (container.getName() == i.container && element.name == i.element) {
										element.state = highlighted;
									}else{
										element.state = deactivated;
									}
								}
							}else{
								if (container.getName() == i.container && element.name == i.element) {
									element.state = highlighted;
								}else{
									if (element.name == "pause") {
										if (element.state != activated) {
											element.state = deactivated;
										}
									}else{
										element.state = deactivated;
									}
								}
							}	
						}else{
							if (element.name == "pause") {
								if (element.state != activated) {
									element.state = deactivated;
								}
							}else{
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
						if (gui.getGuiContainer("Main bar")->getElement("pause")->state == deactivated || gui.getGuiContainer("Main bar")->getElement("pause")->state == highlighted){
							gui.getGuiContainer("Main bar")->getElement("pause")->state = activated;
						}else{
							gui.getGuiContainer("Main bar")->getElement("pause")->state = deactivated;
						}			
					}else if (i.element == "quit") {
						return 0;
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

		window.setView(camera);
		window.clear(sf::Color(50, 50, 50, 255));

		//All the drawing goes here
		drawer::drawPlayingField(window, camera, playing_field, width, height, scale);
		//drawer::drawPlayingFieldDebug(window, camera, playing_field, width, height, scale);

		window.setView(window.getDefaultView());
		gui.drawGUI(window, basicStyle);

		window.display();

		if (frameCounter == 100) {
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			start = std::chrono::high_resolution_clock::now();
			std::cout << round(1000.0/(duration.count()/100.0)) << " FPS on average.\n";
			frameCounter = 0;
		}else{
			frameCounter++;
		}	
	}

	return 0;
}