#include "Game.hpp"
#include "Logger.hpp"
#include "RendererImpl.h"

/// <summary>
/// Constructor sets null pointer to background
/// </summary>
CGame::CGame()
{
	Logger::instance().log(LOGLEVEL::INFO, "Starting Game Class");
	m_pSpriteBackground = NULL;
}

/// <summary>
/// setup the game with initial background image 
/// sets the running variable to true
/// </summary>
void CGame::Init()
{
	m_pSpriteBackground = new CSprite;

	m_pSpriteBackground->Load("../Data/Sprites/Terrain/Background.bmp");

	m_bGameRun = true;
}

/// <summary>
/// quits the game by deleting the background
/// right now no usage because the game cannot be ended in an nonvolatile way
/// </summary>
void CGame::Quit()
{
	if (m_pSpriteBackground != NULL)
	{
		delete (m_pSpriteBackground);
		m_pSpriteBackground = NULL;
	}
}

/// <summary>
/// Main loop of the game
/// calls update and renderer from the framework 
/// </summary>
void CGame::Run()
{
	while (m_bGameRun == true)
	{
		RendererImpl::instance().updateTimer();
		RendererImpl::instance().clearScreen();
		m_pSpriteBackground->Render();
		RendererImpl::instance().render();

	}

}

