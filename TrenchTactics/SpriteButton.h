#pragma once
#include "Sprite.h"
#include "SpriteUnit.h"

/**
 * Extension of sprite with button specific functions.
 */
class SpriteButton :
	public Sprite
{
public:
	void render(bool pressed);

};

