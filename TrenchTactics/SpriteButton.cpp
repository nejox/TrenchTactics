#include "SpriteButton.h"

/**
 * Render a button based on the provided state.
 *
 * \param state the buttonstate that shall be rendered
 */
void SpriteButton::render(STATES::BUTTONSTATE state)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { 0, 0, 64, 64 };
	renderQuad.x = state * 64;
	//Set clip rendering dimensions
	m_Rect.w = renderQuad.w;
	m_Rect.h = renderQuad.h;

	//Render to screen
	SDL_RenderCopy(m_pRenderer, m_pImage, &renderQuad, &m_Rect);

}

/*
void SpriteButton::render()
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { 0, 0, 64, 64 };
	this->x = 1 - this->x;
	renderQuad.x = x * 64;
	//Set clip rendering dimensions
	m_Rect.w = renderQuad.w;
	m_Rect.h = renderQuad.h;

	//Render to screen
	SDL_RenderCopy(m_pRenderer, m_pImage, &renderQuad, &m_Rect);
}
*/
