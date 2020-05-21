#pragma once
#include "Sprite.hpp"

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