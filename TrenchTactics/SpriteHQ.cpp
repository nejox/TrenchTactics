#include "SpriteHQ.h"

SpriteHQ::SpriteHQ(const std::string filename, int numFrames)
{
	this->load(filename, 2, 128, 128);
}

void SpriteHQ::render(state health)
{
	// Ausschnitt der aktuellen Animationsphase berechnen
	m_FrameRect.x = (health * m_FrameWidth);
	m_FrameRect.y = 0;

	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
}
