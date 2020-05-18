#pragma once
#include "RendererImpl.h"
#include "Framework.hpp"
#include "Logger.hpp"
#include <string>


//-TTF einbinden nervt ab, ihr müsst das genau so machen wie bei SDL2 (include und lib), 
//beim linker schreibt ihr den kompletten pfad zur lib datei rein -> quasi "C:/bla/blabla/SDL_TTF/blablabla/lib
//bei mir gings nur so und ihr müsst alle .dll files in den debug ordner ziehen, falls nicht automatisch beim pull passiert

/**
 * SpriteText class the provides a possibility to render a specific text base on sdl ttf backend.
 */
class SpriteText
{
public:


	/**
	 * Initializes textsprite by initializing Font in given size
	 *
	 * \param size
	 */
	SpriteText(int size);


	/**sets position to text, takes the X and Y positions of the tile, not absolute values
	*/
	void setPosGrid(int tileX, int tileY)
	{
		this->m_posX = tileX * 64;
		this->m_posY = tileY * 64;
		this->m_Rect.x = tileX * 64;
		this->m_Rect.y = tileY * 64;
	}

	/**sets position to text, takes the absolute X and Y values
*/
	void setPos(int x, int y)
	{
		this->m_posX = x;
		this->m_posY = y;
		this->m_Rect.x = x;
		this->m_Rect.y = y;
	}

	int getX()
	{
		return m_posX;
	}

	int getY()
	{
		return m_posY;
	}

	/** Destroys the text sprite by closing the font and destroying the teture
	*/
	~SpriteText();

	void load(std::string text);
	void render();


private:
	TTF_Font* m_font;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pText;
	SDL_Rect m_Rect;
	int m_posX;
	int m_posY;

};