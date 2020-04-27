#pragma once
#include "Tile.h"
#include "Button.h"

/**
 * MenuTile class for holding and locating Buttons
 */
class MenuTile : public Tile {
private:
	std::shared_ptr<Button> button;
public:
	void setButton(std::shared_ptr<Button> button) {
		this->button = button;
	}
	std::shared_ptr<Button> getButton() {
		return this->button;
	}
	int handleEvent();
	MenuTile() {};
	~MenuTile() {};

};