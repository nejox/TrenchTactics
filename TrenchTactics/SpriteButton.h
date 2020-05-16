#pragma once
#include "Sprite.hpp"
#include "SpriteUnit.h"

class SpriteButton :
	public Sprite
{
public:
	int x;
	void render(bool pressed);
	void render();

};

