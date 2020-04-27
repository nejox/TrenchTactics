#include "SpriteUnit.h"

SpriteUnit::SpriteUnit(const std::string filename)
{
	this->m_currentPhase = 0;
	this->setAnimation(filename);
}

void SpriteUnit::setAnimation(const std::string filename)
{

	this->load(filename, 64, 64);

}

void SpriteUnit::render()
{
	// Ausschnitt der aktuellen Animationsphase berechnen
	m_FrameRect.x = ((m_currentPhase % m_NumFrames) * m_FrameWidth);
	m_FrameRect.y = 0;

	m_currentPhase++;
	
	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
}
