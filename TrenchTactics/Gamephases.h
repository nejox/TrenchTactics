#pragma once

/**
 * GAMPHASES namespace
 * has the gamephase enum as well as an identifier which returns an array of all gamephases
 */
namespace GAMEPHASES {
	enum GAMEPHASE
	{
		BUY,
		MOVE,
		ATTACK
	};
	static const GAMEPHASE All[] = { BUY, MOVE, ATTACK };

	enum TUTORIALPHASE {
		INTRO,
		MENU,
		UNITS,
		TUT_BUY,
		TUT_MOVE,
		TUT_ATTACK
	};
	static const TUTORIALPHASE TutAll[] = { INTRO, MENU, UNITS, TUT_BUY, TUT_MOVE, TUT_ATTACK };

}