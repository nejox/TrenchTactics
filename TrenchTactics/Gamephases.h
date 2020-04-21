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

}