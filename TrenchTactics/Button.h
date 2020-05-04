#pragma once
#include "Sprite.hpp"

class Button {
private:
	Sprite* sprite;
	int type;

public:
	void setSprite(Sprite* sprite) {
		this->sprite = sprite;
	}

	Sprite* getSprite() {
		return this->sprite;
	}

	void setType(int type) {
		this->type = type;
	}

	int getType() {
		return this->type;
	}
	Button() {
		this->type = -1;
		this->sprite = NULL;
	}
	~Button() {};
};