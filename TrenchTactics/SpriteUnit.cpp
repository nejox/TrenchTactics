#pragma once

#include "SpriteUnit.h"
#include "Sprite.hpp"
#include "ConfigReader.h"
#include "Timer.hpp"

SpriteUnit::SpriteUnit(bool colourRed, TYPES::UnitType type)
{
	m_colourRed = colourRed;
	m_defaultState = STATES::UNITSTATE::STANDING_NEUTRAL;
	m_currentState = m_defaultState;
	m_fcurrentPhase = 0;

	std::shared_ptr<UnitConf> unitConf = ConfigReader::instance().getUnitConf(type);

	// Setting the respective Paths to Animation Files
	for (STATES::UNITSTATE state : STATES::All) {

		switch (state)
		{
		case STATES::STANDING_NEUTRAL:
			if (colourRed) {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, unitConf->getSpriteFilePathStandingNeutralRed()));
			}
			else
			{
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, unitConf->getSpriteFilePathStandingNeutralBlue()));
			}
			break;
		case STATES::STANDING:
			if (colourRed) {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, unitConf->getSpriteFilePathStandingActiveRed()));
			}
			else
			{
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, unitConf->getSpriteFilePathStandingActiveBlue()));
			}
			break;
		case STATES::SHOOTING:
			if (colourRed) {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, unitConf->getSpriteFilePathShootingRed()));
			}
			else {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, unitConf->getSpriteFilePathShootingBlue()));
			}
			break;
		case STATES::RUNNING:
			if (colourRed) {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, unitConf->getSpriteFilePathRunningRed()));
			}
			else {
				animations.insert(std::pair<STATES::UNITSTATE, string>(state, unitConf->getSpriteFilePathRunningBlue()));
			}
			break;
		default:
			break;
		}
	}

	load(animations.at(m_currentState), 64, 64);
}

void SpriteUnit::render()
{
	//calculate currentPhase
	m_fcurrentPhase += 5.0f * CTimer::Get()->GetElapsed();
	//m_fcurrentPhase++;
	int actFrame = static_cast<int>(m_fcurrentPhase)%m_numFrames;
	// Ausschnitt der aktuellen Animationsphase berechnen
	if (m_currentState == m_defaultState) {
		actFrame = actFrame % m_numFrames;
	}/*
	else
	{
		if (actFrame >= m_numFrames) {
			//animation over - load default one
			m_currentState = m_defaultState;
			load(animations.at(m_currentState), 64, 64);
			actFrame = 0;
		}
	}*/

	render(actFrame);
}

void SpriteUnit::render(STATES::UNITSTATE state)
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
}

void SpriteUnit::render(int frame) {
	m_FrameRect.x = frame * m_frameWidth;
	m_FrameRect.y = 0;

	// Ausschnitt rendern
	SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);
}

/**
 *
 * \param sFilename
 * \param FrameWidth
 * \param FrameHeight
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
	m_numFrames = m_Rect.w / m_frameWidth;; //wie viele einzelbilder

	// Ziel-Rect korrigieren
	m_Rect.w = frameWidth; // den aktuellen teil der animation
	m_Rect.h = frameHeight;
	// Current phase to 0
	m_fcurrentPhase = 0;
}

