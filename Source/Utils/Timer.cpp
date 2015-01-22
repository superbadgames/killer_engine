#include <Timer.h>

Timer::Timer(F32 startTimerSeconds = 0.0f) {
	_timeCyles = _SecondsToCycles(startTimerSeconds);
	_timeScale = 1.0f;
	_isPaused  = false;
}

void Timer::Init(){ _frequency = (F32)QueryPerformanceFrequency(); }

void Timer::Update() {
	if(!_isPaused) {
		U64 dtScaledCycles = _SecondsToCycles(_deltaTime * _timeScale);

		_deltaTime 

		_timeCyles += dtScaledCycles;
		_deltaTime  = 
	}
}

void Timer::SingleStep() {
	if(!_isPaused) {
		U64 dtScaledCycles = _SecondsToCycles((1.0f/30.0f) * _timeScale);

		_timeCyles += dtScaledCycles;
	}
}