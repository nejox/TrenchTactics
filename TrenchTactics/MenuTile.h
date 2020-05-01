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
		button.get()->getSprite()->setPos(this->getPosX(), this->getPosY());
		this->button = button;
		this->button.get()->getSprite()->render(64, 0);
	}
	std::shared_ptr<Button> getButton() {
		return this->button;
	}
	int handleEvent();
	MenuTile() {};
	~MenuTile() {};

};