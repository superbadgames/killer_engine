#include <Engine/Controller.h>

namespace KillerEngine 
{
	
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
//=======================================================================================================
//Instance
//=======================================================================================================
	Controller* Controller::_instance = NULL;

	Controller* Controller::Instance(void) 
	{
		if (_instance == NULL) { _instance = new Controller(); }
		return _instance;
	}
	

//=======================================================================================================
//Shutdown
//=======================================================================================================
	void Controller::ShutDown(void) 
	{  }		
	
//==========================================================================================================================
//
//Controller Functions
//
//==========================================================================================================================
	void Controller::Update(void)
	{
		for(int i = 0; i < _totalKeys; ++i)
		{
			//check if key was just pressed
			if(!_pastActiveKeys[i] && _curActiveKeys[i])
				_keyStates[i] = KeyStates::KEY_DOWN;

			//check if key is being held
			if(_pastActiveKeys[i] && _curActiveKeys[i])
				_keyStates[i] = KeyStates::KEY_HELD;

			//check if key has been release this frame
			if(_pastActiveKeys[i] && !_curActiveKeys[i])
				_keyStates[i] = KeyStates::KEY_UP;

			//check if key is not being pressed
			if(!_pastActiveKeys[i] && !_curActiveKeys[i] )
				_keyStates[i] = KeyStates::KEY_RELEASED;

			//Save current state for next frame
			_pastActiveKeys[i] = _curActiveKeys[i];
		}
	}

//=======================================================================================================
//KeyState Accessors
//=======================================================================================================
	bool Controller::GetKeyDown(Keys k)
	{
		if(_keyStates[k] == KeyStates::KEY_DOWN) { return true; }
		else 									 { return false; }
	}

	bool Controller::GetKeyHeld(Keys k)
	{
		if(_keyStates[k] == KeyStates::KEY_HELD) { return true; }
		else									{ return false; }
	}

	bool Controller::GetKeyUp(Keys k)
	{
		if(_keyStates[k] == KeyStates::KEY_UP) { return true; }
		else								   { return false; }
	}

	bool Controller::GetKeyReleased(Keys k)
	{
		if(_keyStates[k] == KeyStates::KEY_RELEASED) { return true; }
		else										 { return false; }
	}

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
	Controller::Controller(void) : _transform()
	{
		for(int i = 0; i < _totalKeys; ++i)
		{
			_curActiveKeys[i] = false;//KeyStates::KEY_RELEASED;
			_pastActiveKeys[i] = false; //KeyStates::KEY_RELEASED;
		}
	}

}//End namespace	