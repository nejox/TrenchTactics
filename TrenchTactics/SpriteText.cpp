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

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(m_pText, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { m_posX, m_posY, texW, texH };

	/*
	m_Rect.x = m_posX;
	m_Rect.y = m_posY;
	m_Rect.w = text_surface->w;
	m_Rect.h = text_surface->h;
	*/
	
	SDL_FreeSurface(text_surface);
}

void SpriteText::render()
{
	SDL_RenderCopy(m_pRenderer, m_pText, NULL, &m_Rect);
}

void SpriteText::render(int locX, int locY) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { locX, locY, 64, 64 };

	//Set clip rendering dimensions
	m_Rect.w = renderQuad.w;
	m_Rect.h = renderQuad.h;

	//Render to screen
	SDL_RenderCopy(m_pRenderer, m_pText, &renderQuad, &m_Rect);
}
