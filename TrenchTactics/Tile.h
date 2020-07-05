#pragma once
#include "Sprite.h"
#include "SpriteMarker.h"
#include "MouseClickEvent.h"

/**
 * Tileclass with relevant information, setters and getters.
 */
class Tile {
private:
	bool marked = false;
	bool selected = false;
	std::shared_ptr<Sprite> sprite;
	std::shared_ptr<SpriteMarker> spriteMarker;
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
	void setSprite(std::shared_ptr < Sprite> sprite) {
		this->sprite = sprite;
	}
	std::shared_ptr<Sprite> getSprite() {
		return this->sprite;
	}
	void setMarker(std::shared_ptr<SpriteMarker> marker) {
		this->spriteMarker = marker;
	}
	std::shared_ptr<SpriteMarker> getMarker() {
		return this->spriteMarker;
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