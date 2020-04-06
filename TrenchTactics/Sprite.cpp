#include "Sprite.hpp"

/// <summary>
/// Sprite class constructor which gets the pointer to the renderer from the framework
/// </summary>
CSprite::CSprite()
{
	m_pRenderer = g_pFramework->GetRenderer();
	m_pImage = NULL;
}

/// <summary>
/// Sprite class destructor which destroys the texture saved in the sprite class
/// </summary>
CSprite::~CSprite()
{
	SDL_DestroyTexture(m_pImage);
}


/// <summary>
/// function which loads a sprite from the specified file name
/// provides an error messages if it doesnt work
/// This also sets colorkey and creates a texture 
/// </summary>
/// <param name="sFilename">path to the img which will be loaded</param>
void CSprite::Load(const string sFilename)
{
	SDL_Surface* pTemp = SDL_LoadBMP(sFilename.c_str());

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

/// <summary>
/// wraps rendercopy of SDL Framework
/// takes renderer from the sprite class and the image to display it on screen at givven rect from sprite
/// </summary>
void CSprite::Render()
{
	SDL_RenderCopy(m_pRenderer, m_pImage, NULL, &m_Rect);
}
