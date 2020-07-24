#ifndef SPRITE_HEADER
#define SPRITE_HEADER
#include "IRenderer.h"


/**
 * Base sprite class with sdl backend.
 */
class Sprite
{
public:
	Sprite();
	~Sprite();

	void setPos(int x, int y);
	int getX();
	int getY();
	void load(const std::string sFilename);
	void render(int locX, int locY);
	void render();
	//virtual void render(int frameNumber);

protected:

	SDL_Renderer* m_pRenderer;	// Zeiger auf den Renderer
	SDL_Texture*  m_pImage;		// Das eigentliche Bild des Sprites
	SDL_Rect	  m_Rect;		// Rect des Sprites
	SDL_Rect	  m_FrameRect;	// Ausschnitt für Animationsphase
	int m_posX;
	int m_posY;
	int quadX;
	int quadY;
};
#endif

