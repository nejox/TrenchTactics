#pragma once
#include "Timer.hpp"
#include <SDL_ttf.h>
#include <iostream>

/**
 * Renderer Interface with all necessary virtual functions.
 */
class IRenderer
{
public:

	virtual bool init(int ScreenWidth, int ScreenHeight,
		int ColorDepth, bool bFullscreen) = 0;
	virtual void clearScreen() = 0;
	virtual void destroy() = 0;
	virtual void updateTimer() = 0;

	virtual ~IRenderer() {}

private:
	CTimer* timer;

};