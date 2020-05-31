#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL.h>
#include "Singleton.hpp"

#define g_pTimer CTimer::Get ()
/**
 * Timer class which provides the current time and can be updated each tick.
 */
class CTimer : public TSingleton<CTimer>
{
public:
	CTimer();
	void  Update();
	float GetElapsed() { return m_fElapsed; }

private:
	float m_fElapsed;
	float m_fCurTime;
	float m_fLastTime;

};

#endif
