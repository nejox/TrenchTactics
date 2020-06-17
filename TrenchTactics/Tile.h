#pragma once
#include "Sprite.hpp"
#include "MouseClickEvent.h"

/**
 * Tileclass with relevant information, setters and getters.
 */
class Tile {
private:
	bool marked = false;
	bool selected = false;
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
		this->sprite->setPos(x, y);

	}
	int getPosY() {
		return this->posY;
	}
	int getPosX() {
		return this->posX;
	}

	Tile() {
		this->marked = false;
		this->selected = false;
		this->sprite = NULL;
	}
};