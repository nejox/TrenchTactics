#include "Sprite.hpp"

CSprite::CSprite()
{
	m_pRenderer = g_pFramework->GetRenderer();

}

CSprite::~CSprite()
{
	SDL_DestroyTexture(m_pImage);
}

void CSprite::Load(const string sFilename)
{
	SDL_Surface *pTemp = SDL_LoadBMP(sFilename.c_str());

	if (pTemp == NULL)
	{
		cout << "Fehler beim Laden von: " << sFilename.c_str();
		cout << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		g_pFramework->Quit();

		exit(1);
	}

	SDL_SetColorKey(pTemp, SDL_TRUE, SDL_MapRGB(pTemp->format, 255, 0, 255));

	m_pImage = SDL_CreateTextureFromSurface(m_pRenderer, pTemp);

	m_Rect.x = 0;
	m_Rect.y = 0;
	m_Rect.w = pTemp->w;
	m_Rect.h = pTemp->h;

	SDL_FreeSurface(pTemp);

}


void CSprite::Render()
{
	SDL_RenderCopy(m_pRenderer, m_pImage, NULL, &m_Rect);
}
