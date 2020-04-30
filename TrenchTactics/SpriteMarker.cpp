#pragma once
#include "SpriteMarker.h"

void SpriteMarker::makeTransperant()
{
	SDL_SetTextureBlendMode(m_pImage, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_pImage, 150);
}
