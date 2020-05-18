#include "SpriteHQ.h"
#include "ConfigReader.h";

/**
 * constructor for sprite hq.
 *
 * \param colorRed decied which kind of headequarter sprite will be loaded
 */
SpriteHQ::SpriteHQ(bool colorRed)
{
	m_colourRed = colorRed;
	m_damaged = false;
	if (m_colourRed) {
		m_spritePath = ConfigReader::instance().getTileConf()->getHeadquarterSpriteRed();
	}
	else {
		m_spritePath = ConfigReader::instance().getTileConf()->getHeadquarterSpriteBlue();
	}

	load(m_spritePath, 128, 128);
}

/**
 * render the headquarter - either damged or not.
 *
 * \param damaged
 */
void SpriteHQ::render(bool damaged)
{
	m_damaged = damaged;

	render();
}

/**
 * Standard render function, renders damaged version when damaged
 *
 */
void SpriteHQ::render() {

	// Ausschnitt der aktuellen Animationsphase berechnen
	m_FrameRect.x = (m_damaged * m_frameWidth);
	m_FrameRect.y = 0;

	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
}



/**
 * load the sprite hq from provided file
 * \param sFilename filepath to the headquarter sprite
 * \param FrameWidth width of the sprite
 * \param FrameHeight height of the sprite
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