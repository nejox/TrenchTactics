#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Framework.hpp"

class CSprite
{
public:
	CSprite();
	~CSprite();

	void Load(const string sFilename);
	void Render();

private:
	SDL_Renderer *m_pRenderer;
	SDL_Texture	 *m_pImage;
	SDL_Rect	  m_Rect;
};

#endif
