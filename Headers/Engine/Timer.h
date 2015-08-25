/*========================================================================
The high precision timer for the Killer1 Engine. At the time of writting
this the timer is windows specific, but cross platform functionality is
planned in the future. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/

#ifndef TIMER_H
#define TIMER_H

//Killer1 includes
#include <Engine/Atom.h>

class Timer { 
private:
	F32  _deltaTime;
	F32  _timeScale;
	F64  _totalTime;
	U64  _pastCycles;
	U64  _curCycles;
	F32  _frequency;
	bool _paused;

	static Timer* _instance;
	
	 inline U64 _SecondsToCycles(F32 timeSeconds) { return (U64)(timeSeconds * _frequency); }
	//WARNING do not use this on big values, very system intensive
	 inline F32 _CyclesToSeconds(U64 timeCycles) { return (F32)timeCycles / _frequency; }

	U64 _QueryHiResTimer(void);
	F32 _QueryFrequency(void);

protected:
	explicit Timer(F64);

public:
	~Timer(void){  }

	static Timer* Instance(void);
	
	//Called once per frame to update time
	void Update    (void);
	void SingleStep(void);

	//Setters and Getters
	void SetPaused(bool paused) { _paused = paused; }
	bool GetPaused(void)        { return _paused; }

	void SetTimeScale(F32 scale) { _timeScale = scale; }
	F32  GetTimeScale(void)      { return _timeScale; }

	F32 DeltaTime(void) { return _deltaTime; }
	F64 TotalTime(void) { return _totalTime; }

};

#endif