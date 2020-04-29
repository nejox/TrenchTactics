#include "SpriteText.h"

void SpriteText::load(const char* text)
{
	SDL_Color color = { 0,0,0 };

	SDL_Surface* text_surface = TTF_RenderText_Solid(m_font, text, color);

	if (!text_surface) {

		std::string msg = "Fehler beim Laden von Text \n Fehlermeldung: ";
		msg.append(TTF_GetError());

		Logger::instance().log(LOGLEVEL::FATAL, msg);

		RendererImpl::instance().destroy();

		exit(1);
	}

	
	m_pText = SDL_CreateTextureFromSurface(m_pRenderer, text_surface);


	//TO DO: hier ist der wurm drin
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(m_pText, NULL, NULL, &texW, &texH);
	this->m_Rect = { m_posX, m_posY, texW, texH };
	
	

	SDL_FreeSurface(text_surface);
}

void SpriteText::render()
{
	SDL_RenderCopy(m_pRenderer, m_pText, NULL, &m_Rect);
}


