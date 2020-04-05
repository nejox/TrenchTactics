#include "Framework.hpp"

CFramework::CFramework()
{
	m_pWindow = NULL;
	m_pRenderer = NULL;
}

bool CFramework::Init(int ScreenWidth, int ScreenHeight,
	int ColorDepth, bool bFullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
		cout << "SDL konnte nicht initialisiert werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		Quit();

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
		cout << "SDL-Fenster konnte nicht erzeugt werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		Quit();

		return (false);
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

	if (m_pRenderer == NULL)
	{
		cout << "SDL-Renderer konnte nicht erzeugt werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		Quit();

		return (false);
	}
	return (true);
}

void CFramework::Quit()
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

void CFramework::Update()
{
	g_pTimer->Update();
}

void CFramework::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
}

void CFramework::Render()
{
	SDL_RenderPresent(m_pRenderer);
}

