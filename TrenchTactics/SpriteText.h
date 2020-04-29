#pragma once
#include "RendererImpl.h"
#include "Framework.hpp"
#include "Logger.hpp"
#include <string>

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

	void load(const char* text);
	void render();
	void render(int locX, int locY);

private:
	TTF_Font* m_font;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pText;
	SDL_Rect m_Rect;
	int m_posX;
	int m_posY;

};