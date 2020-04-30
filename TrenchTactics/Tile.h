#pragma once
#include "Sprite.hpp"
#include "MouseClickEvent.h"

/// <summary>
/// Tileclass with relevant information, setters and getters
/// </summary>
class Tile {
private:
	bool marked = false;
	bool selected = false;
	Sprite* sprite;


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
	int startAnimation();
	int update();
	Tile() {};
};