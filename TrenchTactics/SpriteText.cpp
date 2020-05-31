#include "SpriteText.h"


SpriteText::SpriteText(int size)
{
	m_pRenderer = RendererImpl::instance().GetRenderer();
	m_pText = NULL;
	m_posX = 0;
	m_posY = 0;

	this->m_font = TTF_OpenFont(ConfigReader::instance().getTechnicalConf()->getTextFont().c_str(), size);

	if (m_font == NULL)
	{
		std::string msg = "Font konnte nicht gefunden werden!\n Fehlermeldung: ";
		msg.append(TTF_GetError());

		Logger::instance().log(LOGLEVEL::FATAL, msg);

		exit(1);
	}

}


SpriteText::~SpriteText()
{
	TTF_CloseFont(m_font);
	SDL_DestroyTexture(m_pText);
}

/**
 * load a text and create it on a sdl surface so it can be rendered.
 *
 * \param text string representation of the text that you want to display
 */
void SpriteText::load(std::string text)
{
	SDL_Color color = { 0,0,0 };
	const char* ctext = text.c_str();

	SDL_Surface* text_surface = TTF_RenderText_Solid(m_font, ctext, color);

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
	this->m_Rect = { m_posX, m_posY, texW, texH };



	SDL_FreeSurface(text_surface);
}

/**
 * render the text.
 *
 */
void SpriteText::render()
{
	SDL_RenderCopy(m_pRenderer, m_pText, NULL, &m_Rect);
}


