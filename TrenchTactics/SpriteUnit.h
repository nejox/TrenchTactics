#pragma once
#include <map>
#include "Sprite.h"
#include "UnitTypes.h"

/**
 * all states of a unit.
 */
namespace STATES
{
	enum UNITSTATE {
		STANDING_NEUTRAL,
		STANDING_DARK,
		STANDING,
		SHOOTING,
		RUNNING
	};
	static const UNITSTATE All[] = { STANDING_NEUTRAL, STANDING_DARK, STANDING, SHOOTING, RUNNING };

	enum BUTTONSTATE { //TO DO: Woanders hin
		NEUTRAL,
		PRESSED
	};
}

/**
 * Sprite extension with unit specific functions and stuff.
 */
class SpriteUnit :
	public Sprite
	//std::enable_shared_from_this<SpriteUnit>
{
public:

	SpriteUnit(bool colourRed, TYPES::UnitType type);
	void render();
	STATES::UNITSTATE render(STATES::UNITSTATE changedState);

private:
	//SpriteUnit() {};
	bool m_colourRed;
	STATES::UNITSTATE m_defaultState;
	STATES::UNITSTATE m_currentState;

	float m_fcurrentPhase;

	int m_numFrames;		// Anzahl der Animationsphasen
	int m_frameWidth;		// Breite einer Animationsphase
	int m_frameHeight;		// Höhe einer Animationsphase

	std::map<STATES::UNITSTATE, std::string> animations;

	void load(const std::string sFilename, int frameWidth, int frameHeight);
	void render(int frame);

};

