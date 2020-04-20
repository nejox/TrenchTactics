#include "Sprite.hpp"
#include "RendererImpl.h"
#include "Logger.hpp"

/// <summary>
/// Sprite class constructor which gets the pointer to the renderer
/// </summary>
Sprite::Sprite()
{
	m_pRenderer = RendererImpl::instance().GetRenderer();
	m_pImage = NULL;
}

/// <summary>
/// Sprite class destructor which destroys the texture saved in the sprite class
/// </summary>
Sprite::~Sprite()
{
	SDL_DestroyTexture(m_pImage);
}

void Sprite::setPos(int x, int y)
{
	m_Rect.x = x;
	m_Rect.y = y;
}


/// <summary>
/// function which loads a sprite from the specified file name
/// provides an error messages if it doesnt work
/// This also sets colorkey and creates a texture 
/// </summary>
/// <param name="sFilename">path to the img which will be loaded</param>
void Sprite::load(const string sFilename)
{
	SDL_Surface* pTemp = SDL_LoadBMP(sFilename.c_str());

	if (pTemp == NULL)
	{
		std::string msg = "Fehler beim Laden von: " + sFilename + "\n Fehlermeldung: ";
		msg.append(SDL_GetError());

		Logger::instance().log(LOGLEVEL::FATAL, msg);

		RendererImpl::instance().destroy();

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

void Sprite::load(const string sFilename, int NumFrames, int FrameWidth, int FrameHeight)
{
	// Bitmap laden
	load(sFilename);

	// Rect für Animationsphase initialisieren
	m_NumFrames	  = NumFrames; //wie viele einzelbilder
	m_FrameWidth  = FrameWidth;
	m_FrameHeight = FrameHeight;
	m_FrameRect.w = FrameWidth;  // welcher teil der animation
	m_FrameRect.h = FrameHeight;
	m_NumFramesX  = m_Rect.w / m_FrameWidth; //anzahl der frames im bild

	// Ziel-Rect korrigieren
	m_Rect.w = FrameWidth; // den aktuellen teil der animation
	m_Rect.h = FrameHeight;
}



/// <summary>
/// wraps rendercopy of SDL Framework
/// takes renderer from the sprite class and the image to display it on screen at given rect from sprite
/// </summary>
void Sprite::render()
{
	SDL_RenderCopy(m_pRenderer, m_pImage, NULL, &m_Rect);
}

/*
void Sprite::render(int frameNumber)
{
	// Ausschnitt der aktuellen Animationsphase berechnen
	m_FrameRect.x = (frameNumber * m_FrameWidth);
	m_FrameRect.y = 0;
	
	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);

}
*/
