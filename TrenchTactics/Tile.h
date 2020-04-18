#pragma once
#include "Sprite.hpp"
#include "MouseClickEvent.h"

/// <summary>
/// Tileclass with relevant information, setters and getters
/// </summary>
class Tile {
private:
	int xPos;
	int yPos;
	bool marked;
	bool selected;
	CSprite sprite;
	

public:
	void setXPos(int xPos) {
		this->xPos = xPos;
	}
	int getXPos() {
		return this->xPos;
	}
	void setYPos(int yPos) {
		this->yPos = yPos;
	}
	int getYPos() {
		return this->yPos;
	}
	void setMarked(bool marked) {
		this->marked = marked;
	}
	bool getMarked() {
		return this->marked;
	}
	void setSelected(bool selected) {
		this->selected = selected;
	}
	bool getSelected() {
		return this->selected;
	}
	void setSprite(CSprite sprite) {
		this->sprite = sprite;
	}
	CSprite getSprite() {
		return this->sprite;
	}
	int startAnimation() {};
	int update() {};
	Tile() {};
};