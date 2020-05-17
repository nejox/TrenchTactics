#pragma once
#include "Sprite.hpp"
#include "SpriteUnit.h"

/**
 * Extension of sprite with button specific functions.
 */
class SpriteButton :
	public Sprite
{
public:
	int x;
	void render(bool pressed);
	void render();

};

