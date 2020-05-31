#pragma once
#include "Sprite.hpp"
#include "ConfigReader.h"

class Corpse {

public:

	Corpse(int x, int y);
	~Corpse() {};

	void render();


private:
	int reward;
	Sprite* corpseSprite;
	Corpse();
};