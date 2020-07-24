#pragma once
#include "Sprite.h"

/**
 * SpriteMarker wrapper that helps marking sprites with a specific color.
 */
class SpriteMarker :
	public Sprite {

public:
	void makeTransparent();
};
