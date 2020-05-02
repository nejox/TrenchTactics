#pragma once
#include "Tile.h"
#include "Button.h"

/**
 * MenuTile class for holding and locating Buttons
 */
class MenuTile : public Tile {
private:
	std::shared_ptr<Button> button;
	int tileNumber;
public:
	void setButton(std::shared_ptr<Button> button) {
		if (button) {
			button.get()->getSprite()->setPos(this->getPosX(), this->getPosY());
			this->button = button;
			this->button.get()->getSprite()->render(64, 0);
		}
		else {
			this->button = nullptr;
			this->getSprite()->render(this->getPosX(), this->getPosY());
		}
	}
	std::shared_ptr<Button> getButton() {
		return this->button;
	}
	int handleEvent();
	MenuTile() {};
	~MenuTile() {};

};