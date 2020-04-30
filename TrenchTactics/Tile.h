#pragma once
#include "Sprite.hpp"
#include "MouseClickEvent.h"

/// <summary>
/// Tileclass with relevant information, setters and getters
/// </summary>
class Tile {
private:
	bool marked;
	bool selected;
	Sprite* sprite;
	int posX;
	int posY;


public:
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
	void setSprite(Sprite* sprite) {
		this->sprite = sprite;
	}
	Sprite* getSprite() {
		return this->sprite;
	}
	void setPos(int x, int y) {
		this->posY = y;
		this->posX = x;
	}
	int getPosY() {
		return this->posY;
	}
	int getPosX() {
		return this->posX;
	}
	int startAnimation() {};
	int update() {};
	Tile() {
		this->marked = false;
		this->selected = false;
		this->sprite = NULL;
	}
};