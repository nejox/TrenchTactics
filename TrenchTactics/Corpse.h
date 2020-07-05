#pragma once
#include "Sprite.h"
#include "ConfigReader.h"

class Corpse {

public:

	Corpse(int x, int y);
	~Corpse() {};

	void render();


private:
	int reward;
	std::shared_ptr<Sprite> corpseSprite;
	Corpse();
};