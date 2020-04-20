#pragma once
#include "Tile.h"
#include "Button.h"

/// <summary>
/// MenuTile class for holding and locating Buttons
/// </summary>
class MenuTile : public Tile {
private:
	Button button;
public:
	void setButton(Button button) {
		this->button = button;
	}
	Button getButton() {
		return this->button;
	}
	int handleEvent();
	MenuTile() {};
	~MenuTile() {};
	
};