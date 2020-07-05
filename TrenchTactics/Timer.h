#pragma once
#ifndef TIMER_HEADER
#define TIMER_HEADER
#include <SDL.h>


/**
 * Timer class which provides the current time and can be updated each tick.
 */
class Timer 
{
public:
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(Timer&&) = delete;

	static auto& instance() {
		static Timer renderer;
		return renderer;
	}

	
	void  Update();
	float GetElapsed() { return m_fElapsed; }

private:
	Timer();
	float m_fElapsed;
	float m_fCurTime;
	float m_fLastTime;

};
#endif