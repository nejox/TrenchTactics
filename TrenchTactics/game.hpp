#ifndef GAME_HPP
#define GAME_HPP
#include "Sprite.hpp"


class CGame
{
public:
	CGame();

	void Init();
	void Run();
	void Quit();

private:
	Sprite *m_pSpriteBackground;
	bool     m_bGameRun;
};

#endif
