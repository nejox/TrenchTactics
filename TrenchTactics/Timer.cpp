#include "Timer.hpp"

/// <summary>
/// Consturctor which inits the timer with a base times
/// Timer is based on miliseconds
/// </summary>
CTimer::CTimer()
{
	m_fCurTime = 0;
	m_fLastTime = SDL_GetTicks();
	m_fElapsed = 0;
}

/// <summary>
/// updates timer data to the next tick in miliseconds
/// </summary>
void CTimer::Update()
{
	m_fCurTime = SDL_GetTicks();
	m_fElapsed = m_fCurTime - m_fLastTime;
	m_fLastTime = m_fCurTime;
}