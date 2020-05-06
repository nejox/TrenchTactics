#pragma once
#include "SpriteButton.h"

class Button {
private:
	SpriteButton* sprite;
	int type;

public:
	void setSprite(SpriteButton* sprite) {
		this->sprite = sprite;
	}

	SpriteButton* getSprite() {
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

	void update() {
		if (sprite != nullptr) {
			sprite->render();
		}
	}
	void update(STATES::BUTTONSTATE state) {
		sprite->render(state);
	}

};