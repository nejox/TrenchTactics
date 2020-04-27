#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Framework.hpp"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void setPos(int x, int y);
	int getX();
	int getY();
	void load(const string sFilename);
	void render(int locX, int locY);
	void render();

protected:

	SDL_Renderer* m_pRenderer;	// Zeiger auf den Renderer
	SDL_Texture*  m_pImage;		// Das eigentliche Bild des Sprites
	SDL_Rect	  m_Rect;		// Rect des Sprites
	SDL_Rect	  m_FrameRect;	// Ausschnitt für Animationsphase
	int m_posX;
	int m_posY;
};

#endif
