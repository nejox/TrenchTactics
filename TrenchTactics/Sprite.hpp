#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Framework.hpp"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void setPos(int x, int y);
	void load(const string sFilename);
	
	void render();

protected:

	void load(const string sFilename, int FrameWidth, int FrameHeight);

	SDL_Renderer *m_pRenderer;	// Zeiger auf den Renderer
	SDL_Texture  *m_pImage;		// Das eigentliche Bild des Sprites
	SDL_Rect	  m_Rect;		// Rect des Sprites
	SDL_Rect	  m_FrameRect;	// Ausschnitt f�r Animationsphase
	int m_NumFrames;			// Anzahl der Animationsphasen
	int m_FrameWidth;			// Breite einer Animationsphase
	int m_FrameHeight;			// H�he einer Animationsphase
	int m_NumFramesX;			// Wie viele Anim-Phasen in X-Richtung?
};

#endif
