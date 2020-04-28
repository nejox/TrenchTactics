#include "SpriteHQ.h"
#include "ConfigReader.h";

SpriteHQ::SpriteHQ(bool colorRed)
{
	m_colourRed = colorRed;
	m_damaged = false;
	if (m_colourRed) {
		m_spritePath = ConfigReader::instance().getMapConf()->getHeadquarterSpriteRed();
	}
	else {
		m_spritePath = ConfigReader::instance().getMapConf()->getHeadquarterSpriteBlue();
	}



	load(m_spritePath, 128, 128);
}

void SpriteHQ::render(bool damaged)
{
	m_damaged = damaged;
	// Ausschnitt der aktuellen Animationsphase berechnen
	m_FrameRect.x = (m_damaged * m_frameWidth);
	m_FrameRect.y = 0;

	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
}

/**
 *
 * \param sFilename
 * \param FrameWidth
 * \param FrameHeight
 */
void SpriteHQ::load(const string sFilename, int frameWidth, int frameHeight)
{
	// Bitmap laden
	Sprite::load(sFilename);

	// Rect für Animationsphase initialisieren
	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
	m_FrameRect.w = frameWidth;  // welcher teil der animation
	m_FrameRect.h = frameHeight;

	// Ziel-Rect korrigieren
	m_Rect.w = frameWidth; // den aktuellen teil der animation
	m_Rect.h = frameHeight;
}