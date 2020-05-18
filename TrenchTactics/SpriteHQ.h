#pragma once
#include <string>
#include "Sprite.hpp"

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
	string m_spritePath;

	int m_frameWidth;		// Breite einer Animationsphase
	int m_frameHeight;		// Höhe einer Animationsphase

	SpriteHQ();
	void load(const string sFilename, int frameWidth, int frameHeight);

};

