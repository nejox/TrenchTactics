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

	void SpriteHealthBar::render(int maxHP, int currentHP) {
		double percentage = currentHP / maxHP;

		//igitt ich weiß
		if (percentage > 0.9) render(0);
		else if (percentage <= 0.9 && percentage > 0.8) render(1);
		else if (percentage <= 0.8 && percentage > 0.7) render(2);
		else if (percentage <= 0.7 && percentage > 0.6) render(3);
		else if (percentage <= 0.6 && percentage > 0.5) render(4);
		else if (percentage <= 0.5 && percentage > 0.4) render(5);
		else if (percentage <= 0.4 && percentage > 0.3) render(6);
		else if (percentage <= 0.3 && percentage > 0.2) render(7);
		else if (percentage <= 0.2 && percentage > 0.1) render(8);
		else if (percentage <= 0.1 && percentage > 0) render(9);
		else render(10);

	}

	void SpriteHealthBar::render(int frame) {
		m_FrameRect.x = frame * m_frameWidth;
		m_FrameRect.y = 0;

		// Ausschnitt rendern
		SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
	}

private:
	int m_frameWidth;
	int m_frameHeight;
};