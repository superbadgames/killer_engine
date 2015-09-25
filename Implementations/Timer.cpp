#include <Engine/Timer.h>

namespace KillerEngine 
{

//==========================================================================================================================
//
//Private Timer Functions
//
//==========================================================================================================================
//===============================================================================
//_QueryHiResTimer
//===============================================================================
//=====Windows only implemenation=====
	U64 Timer::_QueryHiResTimer(void) 
	{ 
		static LARGE_INTEGER _cycles;
		QueryPerformanceCounter(&_cycles);
		return _cycles.QuadPart;
	}

//===============================================================================
//_QueryFrequence
//===============================================================================
//=====Windows only implemenation=====
	F32 Timer::_QueryFrequency(void) 
	{ 
		static LARGE_INTEGER _freq;
		QueryPerformanceFrequency(&_freq); 
		return F32(_freq.QuadPart);
	}

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================	
//===============================================================================
//Instance
//===============================================================================
	Timer* Timer::_instance = NULL;
	Timer* Timer::Instance(void) 
	{
		if(_instance == NULL) { _instance = new Timer(); }
		return _instance;
	}

//==========================================================================================================================
//
//Timer Functions
//
//==========================================================================================================================	
//===============================================================================
//Update
//===============================================================================
	void Timer::Update(void) 
	{
		if(!_paused) 
		{
			_curCycles  = _QueryHiResTimer();
			_deltaTime  = (_curCycles - _pastCycles) / _frequency * _timeScale;
			_pastCycles = _curCycles;
			if (_deltaTime < 0.00f || _deltaTime > 1.0f) { _deltaTime = 0.03f; }
			_totalTime += _deltaTime;
		}
	}

//===============================================================================
//SingleStep
//===============================================================================
	void Timer::SingleStep(void) 
	{
		if(!_paused) 
		{
			U64 oneStep = _SecondsToCycles((1.0f/30.0f) * _timeScale);

			_deltaTime = _CyclesToSeconds(oneStep);

			_totalTime += _SecondsToCycles(_deltaTime);
		}
	}


//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
	Timer::Timer() : _frequency(_QueryFrequency()),
					 _deltaTime(0.0f),
					 _timeScale(1.0f),
					 _totalTime(0.0f),
					 _pastCycles(_QueryHiResTimer()),
					 _curCycles(_pastCycles),
					 _paused(false) 
	{  }

}//End namespace