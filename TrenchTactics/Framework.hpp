#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Timer.hpp"

using namespace std;

#define g_pFramework CFramework::Get()

class CFramework : public TSingleton<CFramework>
{
public:
	CFramework();
	bool  Init(int ScreenWidth, int ScreenHeight,
		int ColorDepth, bool bFullscreen);
	void  Quit();
	void  Update();
	void  Clear();
	void  Render();
	SDL_Renderer* GetRenderer() { return m_pRenderer; }

private:
	SDL_Window* m_pWindow;	  // SDL-Windows
	SDL_Renderer* m_pRenderer; // SDL-Renderer

};

#endif
