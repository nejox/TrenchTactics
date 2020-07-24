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


void SpriteHealthBar::render(int maxHP, int currentHP) {

	m_FrameRect.x = (10 - ((10 * currentHP) / maxHP)) * m_frameWidth;
	m_FrameRect.y = 0;

	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);

}

void SpriteHealthBar::render(int maxHP, int currentHP, int level) {

	m_FrameRect.x = (10 - ((10 * currentHP) / maxHP)) * m_frameWidth;
	m_FrameRect.y = (level - 1) * m_frameHeight; // needs rework
	

	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);

}
