#pragma once
#include "RendererImpl.h"
#include "Framework.hpp"
#include "Logger.hpp"
#include <string>


//-TTF einbinden nervt ab, ihr müsst das genau so machen wie bei SDL2 (include und lib), 
//beim linker schreibt ihr den kompletten pfad zur lib datei rein -> quasi "C:/bla/blabla/SDL_TTF/blablabla/lib
//bei mir gings nur so und ihr müsst alle .dll files in den debug ordner ziehen, falls nicht automatisch beim pull passiert

class SpriteText
{
public:

	
	SpriteText(int size)
	{
		m_pRenderer = RendererImpl::instance().GetRenderer();
		m_pText = NULL;
		m_posX = 0;
		m_posY = 0;


		//TO DO:
//this->m_font = TTF_OpenFont(ConfigReader::instance()->getBalanceConf()->getPathToFont(), size);
		this->m_font = TTF_OpenFont("../Data/Fonts/BOO_REG.ttf", size);

		if (m_font == NULL)
		{
			std::string msg = "Font konnte nicht gefunden werden!\n Fehlermeldung: ";
			msg.append(TTF_GetError());

			Logger::instance().log(LOGLEVEL::FATAL, msg);

			exit (1);
		}
		else
		{
			std::string msg = "Font wurde geladen.\n";
			Logger::instance().log(LOGLEVEL::INFO, msg);
		}
	}

	//sets position to tile
	void setPosGrid(int tileX, int tileY)
	{
		this->m_posX = tileX * 64;
		this->m_posY = tileY * 64;
		this->m_Rect.x = tileX * 64;
		this->m_Rect.y = tileY * 64;
	}

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

	~SpriteText()
	{
		TTF_CloseFont(m_font);
		SDL_DestroyTexture(m_pText);
	}

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