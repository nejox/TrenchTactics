#pragma once
#include "Sprite.hpp"

class Button {
private:
	CSprite sprite;
	int type;

public:
	void setSprite(CSprite sprite) {
		this->sprite = sprite;
	}

	CSprite getSprite() {
		return this->sprite;
	}

	void setType(int type) {
		this->type = type;
	}

	int getType() {
		return this->type;
	}
	Button();
	~Button();
};
