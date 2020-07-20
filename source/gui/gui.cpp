#include "gui.h"

void GUI::drawGUI(sf::RenderWindow& window, const guiStyle& style) {
	for (auto& i : containers) {
		i.drawGuiContainer(window, style);
	}
}

guiContainer* GUI::getGuiContainer(const std::string& name) {
	for (int i = 0; i < containers.size(); i++) {
		if (containers[i].getName() == name) {
			return &containers[i];
		}
	}

	return nullptr;
}

void GUI::registerContainer(const int start_x, const int start_y, const int width, const int height, const std::string& name) {
	containers.push_back(guiContainer(start_x, start_y, width, height, name));
}

bool GUI::handleEvent(const sf::Event& event) {
	for (auto& i : containers) {
		if (i.isVisible()) {
			if (i.checkEvent(events, event)) {
				return true;
			}
		}
	}
	return false;
}

void GUI::addEvent(const std::string& container, const std::string& element, const int event_type) {
	events.push_back({container, element, event_type, 0});
}