#pragma once
#include "SpriteMarker.h"

void SpriteMarker::makeTransparent()
{
	SDL_SetTextureBlendMode(m_pImage, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_pImage, 130);
}
