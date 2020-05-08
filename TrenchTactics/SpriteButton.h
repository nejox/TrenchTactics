#pragma once
#include "Sprite.hpp"
#include "SpriteUnit.h"

class SpriteButton :
	public Sprite
{
public:
	int x;
	void render(STATES::BUTTONSTATE state);
	void render();

};

