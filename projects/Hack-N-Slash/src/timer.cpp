#include "timer.h"
#include <stdio.h>

#if _WIN32
#include "SDL.h"
#else 
#include "SDL2/SDL.h"
#endif

AV_Timer::AV_Timer()
{
	tickCountFromStart = 0;
	tickCountFromPause = 0;
	isPaused = false;
	isTimerRunning = false;
}

// NOTE(Devan): Start time.
void AV_Timer::StartTimer()
{
	isTimerRunning = true;
	isPaused = false;
	tickCountFromStart = SDL_GetTicks();
	tickCountFromPause = 0;
	printf( "AV_Timer has been started.\n" );
}

// NOTE(Devan): Stop time and zero timer information..
void AV_Timer::StopTimer()
{
	isTimerRunning = false;
	isPaused = false;
	tickCountFromStart = 0;
	tickCountFromPause = 0;
	printf( "AV_Timer has been stopped.\n" );
}

// NOTE(Devan): Pause time and capture the time at pause.
void AV_Timer::PauseTimer()
{
	if ( isTimerRunning && !isPaused )
	{
		isPaused = true;
		tickCountFromPause = SDL_GetTicks() - tickCountFromStart;
		tickCountFromStart = 0;
		printf( "AV_Timer has been Paused.\n" );
	}
}

// NOTE(Devan): Resume from the same time that the game was paused. 
void AV_Timer::ResumeTimer()
{
	if ( isTimerRunning && isPaused )
	{
		isPaused = false;
		tickCountFromStart = SDL_GetTicks() - tickCountFromPause;
		tickCountFromPause = 0;
		printf( "AV_Timer has Resumed.\n" );
	}
}

// NOTE(Devan): Return the current time in the game. Return the time at the game was paused if the game is currently paused. 
unsigned int AV_Timer::GetTicks()
{
	unsigned int time = 0;

	if ( isTimerRunning )
	{
		if ( isPaused )
		{
			time = tickCountFromPause;
		}
		else
		{
			time = SDL_GetTicks() - tickCountFromStart;
		}
	}
	return time;
}

bool AV_Timer::CheckTimerRunning()
{
	return isTimerRunning;
}

bool AV_Timer::CheckTimerPaused()
{
	return isTimerRunning && isPaused;
}


