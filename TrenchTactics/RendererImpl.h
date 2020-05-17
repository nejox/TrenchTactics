#pragma once
#include "IRenderer.h"

/**
 * Renderer Implemantation based on the SDL Render functions.
 */
class RendererImpl :
	public IRenderer
{

public:
	RendererImpl(const RendererImpl&) = delete;
	RendererImpl& operator=(const RendererImpl&) = delete;
	RendererImpl(RendererImpl&&) = delete;
	RendererImpl& operator=(RendererImpl&&) = delete;

	static auto& instance() {
		static RendererImpl renderer;
		return renderer;
	}

	bool init(int ScreenWidth, int ScreenHeight,
		int ColorDepth = 16, bool bFullscreen = false);
	void clearScreen();
	void destroy();
	void updateTimer();
	void renderTile(); //TODO: Rect tileRect as parameter
	void renderHQ();
	void startAnimation(); //TODO: Unit* unit as parameter

	void render();
	SDL_Renderer* GetRenderer();

private:
	SDL_Window* m_pWindow;	  // SDL-Windows
	SDL_Renderer* m_pRenderer; // SDL-Renderer

	RendererImpl();
};

