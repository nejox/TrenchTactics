#pragma once
#include "SpriteUnit.h"
#include "Sprite.hpp"
#include "ConfigReader.h"
#include "Timer.hpp"

/**
 * constructor that creates the sprite of unit based on color and unittype.
 *
 * \param colourRed decide which sprite will be used
 * \param type enum value of which unit type will be used
 */
SpriteUnit::SpriteUnit(bool colourRed, TYPES::UnitType type)
{
	m_colourRed = colourRed;
	m_defaultState = STATES::UNITSTATE::STANDING_DARK;
	m_currentState = m_defaultState;
	m_fcurrentPhase = 0;

	// Setting the respective Paths to Animation Files
	for (STATES::UNITSTATE state : STATES::All) {

		switch (state)
		{
		case STATES::STANDING_NEUTRAL:
			if (colourRed) {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathStandingNeutralRed()));
			}
			else
			{
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathStandingNeutralBlue()));
			}
			break;
		case STATES::STANDING_DARK:
			if (colourRed) {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathStandingDarkRed()));
			}
			else
			{
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathStandingDarkBlue()));
			}
			break;
		case STATES::STANDING:
			if (colourRed) {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathStandingActiveRed()));
			}
			else
			{
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathStandingActiveBlue()));
			}
			break;
		case STATES::SHOOTING:
			if (colourRed) {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathShootingRed()));
			}
			else {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathShootingBlue()));
			}
			break;
		case STATES::RUNNING:
			if (colourRed) {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathRunningRed()));
			}
			else {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, ConfigReader::instance().getUnitConf(type)->getSpriteFilePathRunningBlue()));
			}
			break;
		default:
			break;
		}
	}

	load(animations.at(m_currentState), 64, 64);
}

/**
 * render the sprite of a unit based on the timer and its current state.
 *
 */
void SpriteUnit::render()
{
	//calculate currentPhase
	m_fcurrentPhase += 1.5f * CTimer::Get()->GetElapsed();

	int actFrame = static_cast<int>(m_fcurrentPhase);
	// Ausschnitt der aktuellen Animationsphase berechnen
	if (m_currentState == m_defaultState) {
		actFrame = actFrame % m_numFrames;
	}
	else if (m_currentState == STATES::STANDING) {
		actFrame = actFrame % m_numFrames;
	}
	else
	{
		if (actFrame >= m_numFrames) {
			//animation over - load default one
			m_currentState = m_defaultState;
			load(animations.at(m_currentState), 64, 64);
			actFrame = 0;
		}
	}

	render(actFrame);
}

/**
 * render a specific state of a unit and return the current state of the unit afterwards.
 *
 * \param state unitstate that will be rendered
 * \return the current state of this specific unit after it rendered
 */
STATES::UNITSTATE SpriteUnit::render(STATES::UNITSTATE state)
{
	if (m_currentState == state) {
		render();
	}
	else {
		m_currentState = state;
		// load new animation
		load(animations.at(m_currentState), 64, 64);
		int actFrame = static_cast<int>(m_fcurrentPhase);

		render(actFrame);
	}

	return m_currentState;
}

/**
 * render a specific frame of a unit.
 * based on the state the unit currently has
 *
 * \param frame the value which frame should be rendered
 */
void SpriteUnit::render(int frame) {
	m_FrameRect.x = frame * m_frameWidth;
	m_FrameRect.y = 0;

	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
}

/**
 * load a unitsprite from the provided filepath
 * \param sFilename path to the unitsprite
 * \param FrameWidth width of the sprite
 * \param FrameHeight height of the sprite
 */
void SpriteUnit::load(const std::string sFilename, int frameWidth, int frameHeight)
{
	// Bitmap laden
	Sprite::load(sFilename);

	// Rect für Animationsphase initialisieren
	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
	m_FrameRect.w = frameWidth;  // welcher teil der animation
	m_FrameRect.h = frameHeight;
	m_numFrames = m_Rect.w / m_frameWidth; //wie viele einzelbilder

	// Ziel-Rect korrigieren
	m_Rect.w = frameWidth; // den aktuellen teil der animation
	m_Rect.h = frameHeight;
	// Current phase to 0
	m_fcurrentPhase = 0;
}

