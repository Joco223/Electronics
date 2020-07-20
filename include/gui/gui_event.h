#pragma once

#include <string>

enum eventTypes {
	leftClick,
	rightClick,
	mouseOver,
	mouseScroll,
	other
};

class guiEvent {
public:
	std::string container, element;
	int event_type, amount;

	guiEvent() : container(""), element(""), event_type(-1), amount(0) {}
	guiEvent(const std::string& container_, const std::string& element_, const int event_type_, const int amount_) 
		: container(container_), element(element_), event_type(event_type_), amount(amount_) {};
};