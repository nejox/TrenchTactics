#pragma once

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
	m_posX = 0;
	m_posY = 0;
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
	this->m_posX = x;
	this->m_posY = y;
	this->m_Rect.x = x;
	this->m_Rect.y = y;
}

int Sprite::getX()
{
	return m_posX;
}

int Sprite::getY()
{
	return m_posY;
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

	m_Rect.x = m_posX;
	m_Rect.y = m_posY;
	m_Rect.w = pTemp->w;
	m_Rect.h = pTemp->h;

	SDL_FreeSurface(pTemp);
}


/**
 * wraps rendercopy of SDL Framework
 * takes renderer from the sprite class and the image to display it on screen at given rect from sprite
 *
 */
void Sprite::render()
{
	SDL_RenderCopy(m_pRenderer, m_pImage, NULL, &m_Rect);
}

/**
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



