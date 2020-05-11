#pragma once
#include "Sprite.hpp"

class SpriteHealthBar :
	public Sprite
{
public:

	enum TYPE { UNIT, HQ};

	SpriteHealthBar(TYPE type) 
	{
		if (type == UNIT)
		{
			this->load("../Data/Sprites/Token/HEALTHBAR_UNIT.bmp");
			m_frameWidth = 64;
			m_frameHeight = 64;
		}

		else if (type == HQ)
		{
			this->load("../Data/Sprites/Token/HEALTHBAR_HQ.bmp");
			m_frameWidth = 128;
			m_frameHeight = 128;
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



private:
	int m_frameWidth;
	int m_frameHeight;

	void SpriteHealthBar::render(int frame) {
		m_FrameRect.x = frame * m_frameWidth;
		m_FrameRect.y = 0;

		// Ausschnitt rendern
		SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
	}
};