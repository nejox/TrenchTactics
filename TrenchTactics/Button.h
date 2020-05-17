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

	/**
	 * update the buttonsprite in its current state
	 * 
	 */
	void update() {
		if (sprite != nullptr) {
			sprite->render();
		}
	}
	/**
	 * update a button with the given state
	 * 
	 * \param state 
	 */
	void update(STATES::BUTTONSTATE state) {
		if (sprite != nullptr) {
			sprite->render(state);
		}
	}

};