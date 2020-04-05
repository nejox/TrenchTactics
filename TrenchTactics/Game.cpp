#include "Game.hpp"

CGame::CGame()
{
	m_pSpriteBackground = NULL;
}

void CGame::Init()
{
	m_pSpriteBackground = new CSprite;
	m_pSpriteBackground->Load("../Data/Background.bmp");

	m_bGameRun = true;
}

void CGame::Quit()
{
	if (m_pSpriteBackground != NULL)
	{
		delete (m_pSpriteBackground);
		m_pSpriteBackground = NULL;
	}
}

void CGame::Run()
{
	while (m_bGameRun == true)
	{
		g_pFramework->Update();
		g_pFramework->Clear();
		m_pSpriteBackground->Render();
		g_pFramework->Render();

	}

}

