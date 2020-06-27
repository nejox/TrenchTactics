#include "Timer.h"

/**
 * Constructor which inits the timer with a base times.
 *
 */
Timer::Timer()
{
	m_fCurTime = 0.0f;
	m_fLastTime = SDL_GetTicks() / 1000.0f;
	m_fElapsed = 0.0f;
}

/**
 * updates timer data to the next tick.
 *
 */
void Timer::Update()
{
	m_fCurTime = SDL_GetTicks() / 1000.0f;
	m_fElapsed = m_fCurTime - m_fLastTime;
	m_fLastTime = m_fCurTime;
}