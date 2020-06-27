#pragma once
#include "Sprite.h"
#include "ConfigReader.h"

/**
 * Sprite extension for the headquarter.
 */
class SpriteHQ : public Sprite
{
public:
	SpriteHQ(bool colorRed);
	void render(bool damaged);
	void render();

private:
	bool m_colourRed;
	bool m_damaged;
	std::string m_spritePath;

	int m_frameWidth;		// Breite einer Animationsphase
	int m_frameHeight;		// Höhe einer Animationsphase

	SpriteHQ();
	void load(const std::string sFilename, int frameWidth, int frameHeight);

};

