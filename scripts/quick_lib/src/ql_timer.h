#ifdef _WIN32
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

// header
#ifndef QL_TIMER_H
#define QL_TIMER_H
class QL_Timer
{
public:
	QL_Timer();
	~QL_Timer();
	void QL_StartTimer();
	void QL_StopTimer();
	void QL_PauseTimer();
	void QL_UnpauseTimer();
	Uint32 QL_GetTicks();
	bool QL_CheckStarted();
	bool QL_CheckPaused();
private:
	Uint32 start_ticks;
	Uint32 paused_ticks;
	bool is_paused;
	bool is_started;
};
#endif

// implementation
#ifdef QL_TIMERS
QL_Timer::QL_Timer()
{
	start_ticks = 0;
	paused_ticks = 0;
	is_paused = false;
	is_started = false;
}

QL_Timer::~QL_Timer()
{
}

void QL_Timer::QL_StartTimer()
{
	is_started = true;
	is_paused = false;
	start_ticks = SDL_GetTicks();
	paused_ticks = 0;
}

void QL_Timer::QL_StopTimer()
{
	is_started = false;
	is_paused = false;
	start_ticks = 0;
	paused_ticks = 0;
}

void QL_Timer::QL_PauseTimer()
{
	if ( is_started && !is_paused )
	{
		is_paused = true;
		paused_ticks = SDL_GetTicks() - start_ticks;
		start_ticks = 0;
	}
}

void QL_Timer::QL_UnpauseTimer()
{
	if ( is_started && is_paused )
	{
		is_paused = false;
		start_ticks = SDL_GetTicks() - paused_ticks;
		paused_ticks = 0;
	}
}

Uint32 QL_Timer::QL_GetTicks()
{
	Uint32 time = 0;
	if ( is_started )
	{
		if ( is_paused )
		{
			time = paused_ticks;
		}
		else
		{
			time = SDL_GetTicks() - start_ticks;
		}
	}
return time;
}

bool QL_Timer::QL_CheckStarted()
{
	return is_started;
}

bool QL_Timer::QL_CheckPaused()
{
	return is_paused;
}
#endif
