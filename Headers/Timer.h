#ifndef TIMER_H
#define TIMER_H

//Killer1 includes
#include <Atom.h>

class Timer {
	static F32  _frequency;
	       F32  _deltaTime;
		   F32  _timeScale;
		   U64  _totalTimeCycles;
		   U64  _pastFrameTimeCycles;
		   U64  _currentFrameTimeCycles;
		   bool	_isPaused;

public:
	Timer(){}
	explicit Timer(F32 startTimeSeconts = 0.0f);

	~Timer(){}

	void Init();
	
	//Get current time in cycles
	U64 GetTimeCycles() const { return _timeCycles; }

	//calcDeltaSeconds here

	//Called once per frame to update time
	void Update();

	void SingleStep();

	//Setters and Getters
	void SetPaused() { _isPaused = true; }
	bool GetPaused()  { return _isPaused; }

	void SetTimeScale(F32 scale) { _timeScale = scale; }
	F32  GetTimeScale()          { return _timeScale; }

	void GetDeltaTime() const { return _deltaTime; }

private:	
	static inline U64 _CyclesToSeconds(F32 timeSeconds) { return (U64)(timeSeconds * _frequency); }
	//WARNING do not use this on big values, very system intensive
	static inline F32 _SecondsToCyles(U64 timeCyles) { return (F32)timeCyles / _frequency; }
};

#endif