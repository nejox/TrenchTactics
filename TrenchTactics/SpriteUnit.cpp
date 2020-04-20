#include "SpriteUnit.h"

SpriteUnit::SpriteUnit()
{
	this->m_actualPhase = 0;
}

void SpriteUnit::setAnimation(const std::string filename)
{

	this->load(filename, 64, 64);

}

void SpriteUnit::render()
{
	// Ausschnitt der aktuellen Animationsphase berechnen
	m_FrameRect.x = (m_actualPhase * m_FrameWidth);
	m_FrameRect.y = 0;

	m_actualPhase++;
	if (m_actualPhase >= m_NumFrames) {
		m_actualPhase = 0;
	}
	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
}
