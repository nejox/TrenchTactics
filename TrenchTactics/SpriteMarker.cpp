#pragma once
#include "SpriteMarker.h"

/**
 * makes a given tile transparent.
 *
 */
void SpriteMarker::makeTransparent()
{
	SDL_SetTextureBlendMode(m_pImage, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_pImage, 90);
}
