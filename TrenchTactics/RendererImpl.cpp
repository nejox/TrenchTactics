#include <iostream>

#include "RendererImpl.h"
#include "Logger.hpp"
#include <string>

/// <summary>
/// Render constructor which sets both pointers to null pointers
/// </summary>
RendererImpl::RendererImpl() {
	m_pWindow = NULL;
	m_pRenderer = NULL;
}

/// <summary>
/// Init function which wraps the init of SDL
/// Also creates a sdl window as well as the renderer
/// On the way checks wether creation of all those things was succesfull
/// </summary>
/// <param name="ScreenWidth">int value to specifiy screen width</param>
/// <param name="ScreenHeight">int value to specifiy screen height</param>
/// <param name="ColorDepth">int specify colordepth standard value should be 16</param>
/// <param name="bFullscreen">fullscreen or not</param>
/// <returns></returns>
bool RendererImpl::init(int ScreenWidth, int ScreenHeight,
	int ColorDepth, bool bFullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
		std::string msg = "SDL konnte nicht initialisiert werden!\n Fehlermeldung: ";
		msg.append(SDL_GetError());

		Logger::instance().log(LOGLEVEL::FATAL, msg);

		destroy();

		return (false);
	}

	Uint32 WindowFlags = 0;

	if (bFullscreen == true)
		WindowFlags = SDL_WINDOW_FULLSCREEN;
	else
		WindowFlags = SDL_WINDOW_SHOWN;

	m_pWindow = SDL_CreateWindow("SDL_Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		ScreenWidth,
		ScreenHeight,
		WindowFlags);

	if (m_pWindow == NULL)
	{
		std::string msg = "SDL-Fenster konnte nicht erzeugt werden!\n Fehlermeldung: ";
		msg.append(SDL_GetError());

		Logger::instance().log(LOGLEVEL::FATAL, msg);

		destroy();

		return (false);
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

	if (m_pRenderer == NULL)
	{
		std::string msg = "SDL-Renderer konnte nicht erzeugt werden!\n Fehlermeldung: ";
		msg.append(SDL_GetError());

		Logger::instance().log(LOGLEVEL::FATAL, msg);

		destroy();

		return (false);
	}
	return (true);
}

/// <summary>
/// Function to clear the screen from previously rendered objects
/// </summary>
void RendererImpl::clearScreen()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
}

/// <summary>
/// Function to quit the renderer class in a controlled way
/// Destroys the window as well as the renderer initialized by the framework beforehand
/// </summary>
void RendererImpl::destroy()
{
	if (m_pRenderer != NULL)
	{
		SDL_DestroyRenderer(m_pRenderer);
	}

	if (m_pWindow != NULL)
	{
		SDL_DestroyWindow(m_pWindow);
	}
	SDL_Quit();
}

/// <summary>
/// Update function only used to update the timer though
/// </summary>
void RendererImpl::updateTimer()
{
	CTimer::Get()->Update();
}

void RendererImpl::renderTile()
{
}

void RendererImpl::renderHQ()
{
}

void RendererImpl::startAnimation()
{
}

void RendererImpl::render()
{
	SDL_RenderPresent(m_pRenderer);
}

SDL_Renderer* RendererImpl::GetRenderer()
{
	return m_pRenderer;
}
