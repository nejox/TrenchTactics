#pragma once
#include "Rect.h"

/// <summary>
/// Tileclass with relevant information, setters and getters
/// </summary>
class Tile {
private:
	int xPos;
	int yPos;
	bool marked;
	bool selected;
	Rect sprite;

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
	void setSprite(Rect sprite) {
		this->sprite = sprite;
	}
	Rect getSprite() {
		return this->sprite;
	}
	Tile();
	startAnimation();
	update();
	virtual handleEvent();
	virtual Tile();
	~Tile();
};