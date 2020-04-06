#include "Framework.hpp"

/// <summary>
/// Framework constructor which sets both pointers to null pointers
/// </summary>
CFramework::CFramework()
{
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

/// <summary>
/// Function to quit the framework class in a controlled way
/// Destroys the window as well as the renderer initialized by the framework beforehand
/// </summary>
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

/// <summary>
/// Update function only used to update the timer though
/// </summary>
void CFramework::Update()
{
	g_pTimer->Update();
}

/// <summary>
/// Function to clear the screen from previously rendered objects
/// </summary>
void CFramework::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
}

/// <summary>
/// 
/// 
/// </summary>
void CFramework::Render()
{
	SDL_RenderPresent(m_pRenderer);
}

