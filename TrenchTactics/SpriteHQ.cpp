#include "SpriteHQ.h"

SpriteHQ::SpriteHQ(const std::string filename)
{
	this->load(filename, 128, 128);
}

void SpriteHQ::render(bool damaged)
{
	// Ausschnitt der aktuellen Animationsphase berechnen
	m_FrameRect.x = (damaged * m_FrameWidth);
	m_FrameRect.y = 0;

	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
}
