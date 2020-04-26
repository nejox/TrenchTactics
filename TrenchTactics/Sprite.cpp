#include "Sprite.hpp"
#include "RendererImpl.h"
#include "Logger.hpp"


/**
 * Sprite class constructor which gets the pointer to the renderer
 *
 */
Sprite::Sprite()
{
	m_pRenderer = RendererImpl::instance().GetRenderer();
	m_pImage = NULL;
}

/**
 * Sprite class destructor which destroys the texture saved in the sprite class
 *
 */
Sprite::~Sprite()
{
	SDL_DestroyTexture(m_pImage);
}

void Sprite::setPos(int x, int y)
{
	m_Rect.x = x;
	m_Rect.y = y;
}

/**
 * function which loads a sprite from the specified file name
 * provides an error messages if it doesnt work
 * This also sets colorkey and creates a texture
 *
 * \param sFilename path to the img which will be loaded
 */
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
/**
 *
 *
 * \param sFilename
 * \param FrameWidth
 * \param FrameHeight
 */
void Sprite::load(const string sFilename, int FrameWidth, int FrameHeight)
{
	// Bitmap laden
	load(sFilename);

	// Rect für Animationsphase initialisieren

	m_FrameWidth = FrameWidth;
	m_FrameHeight = FrameHeight;
	m_FrameRect.w = FrameWidth;  // welcher teil der animation
	m_FrameRect.h = FrameHeight;
	m_NumFramesX = m_Rect.w / m_FrameWidth; //anzahl der frames im bild
	m_NumFrames = m_NumFramesX; //wie viele einzelbilder

	// Ziel-Rect korrigieren
	m_Rect.w = FrameWidth; // den aktuellen teil der animation
	m_Rect.h = FrameHeight;
}

/**
 * wraps rendercopy of SDL Framework
 * takes renderer from the sprite class and the image to display it on screen at given rect from sprite
 *
 */
void Sprite::render()
{
	SDL_RenderCopy(m_pRenderer, m_pImage, NULL, &m_Rect);
	SDL_RenderPresent(m_pRenderer);
}

/**
 *
 *
 * \param locX
 * \param locY
 */
void Sprite::render(int locX, int locY) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { locX, locY, 64, 64 };

	//Set clip rendering dimensions
	m_Rect.w = renderQuad.w;
	m_Rect.h = renderQuad.h;

	//Render to screen
	SDL_RenderCopy(m_pRenderer, m_pImage, &renderQuad, &m_Rect);
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
