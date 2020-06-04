#pragma once
#include "SpriteButton.h"
#include "SpriteText.h"
#include "ConfigReader.h"


class Button {

public:

	enum BUTTONTYPE
	{
		GRENADEUNIT = 0,
		GUNNERUNIT = 1,
		CCUNIT = 2,

		PREVIOUSUNIT = 10,
		NEXTUNIT = 11,
		DIG = 12,

		CONFIRM = 20,
		CANCEL = 21,
		REROLL = 22,
		ADDUNIT = 23,

		ENDTURN = 30,
		NEXTPHASE = 31,

		STARTGAME = 40,
		TUTORIAL = 41,
		EXIT  = 42
	};

	Button(BUTTONTYPE type) {
		this->type = type;
		this->pressed = false;
		this->sprite = new SpriteButton();
		this->costText = make_shared<SpriteText>(20);
		this->loadSpriteFromType(type);
		this->loadCostFromType(type);
	}
	~Button() {};


	void setPressed(bool pressed)
	{
		this->pressed = pressed;
	}

	bool getState()
	{
		return this->pressed;
	}

	void setSprite(SpriteButton* sprite) {
		this->sprite = sprite;
	}

	SpriteButton* getSprite() {
		return this->sprite;
	}

	BUTTONTYPE getType() {
		return this->type;
	}

	void setType(BUTTONTYPE type);
	void setPos(int x, int y);
	void push();

	void update();

private:
	void loadSpriteFromType(int type);
	void loadCostFromType(int type);

	SpriteButton* sprite;
	int cost;
	std::shared_ptr<SpriteText> costText;
	Button::BUTTONTYPE type;
	bool pressed;

};