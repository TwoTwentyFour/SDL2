#ifndef TIMER_H
#define TIMER_H

class AV_Timer
{

public:

	AV_Timer();
	void StartTimer();
	void StopTimer();
	void PauseTimer();
	void ResumeTimer();
	unsigned int GetTicks();
	bool CheckTimerRunning();
	bool CheckTimerPaused();
	
private:
	
	unsigned int tickCountFromStart;
	unsigned int tickCountFromPause;
	bool isPaused;
	bool isTimerRunning;
};

#endif
