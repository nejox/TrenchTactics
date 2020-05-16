#pragma once
#include "SpriteButton.h"

class Button {


public:

	enum BUTTONTYPE
	{
		GRENADEUNIT = 0,
		GUNNERUNIT = 1,
		CCUNIT = 2,

		PREVIOUSUNIT = 10,
		NEXTUNIT = 11,

		CONFIRM = 20,
		CANCEL = 21,
		REROLL = 22,
		ADDUNIT = 23,

		ENDTURN = 30,
		NEXTPHASE = 31
	};

	void setPressed(bool pressed)
	{
		this->pressed = pressed;
	}

	void push()
	{
		this->pressed = (!(this->pressed));
	}

	bool getState()
	{
		return this->pressed;
	}

	void setSprite(SpriteButton* sprite) {
		this->sprite = sprite;
	}

	void setType(BUTTONTYPE type) {
		this->type = type;
		this->loadSpriteFromType(type);
	}

	BUTTONTYPE getType() {
		return this->type;
	}

	void setPos(int x, int y)
	{
		this->sprite->setPos(x, y);
	}

	void loadSpriteFromType(int type)
	{
		if ((int)type == 0) {
			this->sprite->load("../Data/Sprites/Token/GRENADE_TOKEN.bmp");
		}
		else if ((int)type == 1) {
			this->sprite->load("../Data/Sprites/Token/GUNNER_TOKEN.bmp");
		}
		else if ((int)type == 2) {
			this->sprite->load("../Data/Sprites/Token/CC_TOKEN.bmp");
		}
		else if ((int)type == 10) {
			this->sprite->load("../Data/Sprites/Token/PREVIOUSUNIT_TOKEN.bmp");
		}
		else if ((int)type == 11) {
			this->sprite->load("../Data/Sprites/Token/NEXTUNIT_TOKEN.bmp");
		}
		else if ((int)type == 20) {
			this->sprite->load("../Data/Sprites/Token/CONFIRM_TOKEN.bmp");
		}
		else if ((int)type == 21) {
			this->sprite->load("../Data/Sprites/Token/CANCEL_TOKEN.bmp");
		}
		else if ((int)type == 22) {
			this->sprite->load("../Data/Sprites/Token/REROLL_TOKEN.bmp");
		}
		else if ((int)type == 23) {
			this->sprite->load("../Data/Sprites/Token/ADD_TOKEN.bmp");
		}
		else if ((int)type == 30) {
			this->sprite->load("../Data/Sprites/Token/ENDTURN_TOKEN.bmp");
		}
		else if ((int)type == 31) {
			this->sprite->load("../Data/Sprites/Token/NEXTPHASE_TOKEN.bmp");
		}
		else {
			this->sprite->load("../Data/Sprites/Token/BLANK_TOKEN.bmp");
		}
	}

	Button(BUTTONTYPE type) {
		this->type = type;
		this->pressed = false;
		this->sprite = new SpriteButton();
		this->loadSpriteFromType(type);

	}
	~Button() {};

	void update() {
		if (sprite != nullptr) {
			sprite->render(pressed);
		}
	}


private:
	SpriteButton* sprite;
	Button::BUTTONTYPE type;
	bool pressed;

};