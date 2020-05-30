#include "SpriteHealthBar.h"

SpriteHealthBar::SpriteHealthBar()
{

	this->load(hqHealthbarSprite);
	m_frameWidth = 128;
	m_frameHeight = 128;


	// Rect für Animationsphase initialisieren

	m_FrameRect.w = m_frameWidth;  // welcher teil der animation
	m_FrameRect.h = m_frameHeight;


	// Ziel-Rect korrigieren
	m_Rect.w = m_frameWidth; // den aktuellen teil der animation
	m_Rect.h = m_frameHeight;

}

SpriteHealthBar::SpriteHealthBar(bool ColorRed)
{
	if (ColorRed)
	{
		this->load(rHealthbarSprite);
		m_frameWidth = 64;
		m_frameHeight = 64;
	}

	else
	{
		this->load(bHealthbarSprite);
		m_frameWidth = 64;
		m_frameHeight = 64;
	}



	// Rect für Animationsphase initialisieren

	m_FrameRect.w = m_frameWidth;  // welcher teil der animation
	m_FrameRect.h = m_frameHeight;


	// Ziel-Rect korrigieren
	m_Rect.w = m_frameWidth; // den aktuellen teil der animation
	m_Rect.h = m_frameHeight;

}

/**
*Renders the HealthBar dependent on the current percentage of HP
*/
void SpriteHealthBar::render(int maxHP, int currentHP) {


	this->render(10 - ((10 * currentHP) / maxHP));

}

void SpriteHealthBar::render(int frame) {
	m_FrameRect.x = frame * m_frameWidth;
	m_FrameRect.y = 0;

	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
}