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


/* delete this when new version is working

	void Controller::Init(HINSTANCE hInstance, HWND hwnd) 
	{
		HRESULT result;

		result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_directInput, NULL);
		if(FAILED(result)) { _errorManager->SetError(EC_DirectInput, "Failed to Create Input"); }

		result = _directInput->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL);
		if(FAILED(result)) { _errorManager->SetError(EC_DirectInput, "Failed to create Keyboard Device"); }

		result = _keyboard->SetDataFormat(&c_dfDIKeyboard);
		if(FAILED(result)) { _errorManager->SetError(EC_DirectInput, "Failed to set Keyboard DataFormat"); }

		result = _keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if(FAILED(result)) { _errorManager->SetError(EC_DirectInput, "Failed to set Keyboard Cooperative Level"); }

		result = _keyboard->Acquire();
		if(FAILED(result)) { _errorManager->SetError(EC_DirectInput, "Failed to Acquire keyboard"); }
	}

*/


//=======================================================================================================
//Shutdown
//=======================================================================================================
	void Controller::ShutDown(void) 
	{
/*		if(_keyboard) 
		{
			_keyboard->Unacquire();
			_keyboard->Release();
			_keyboard = 0;
		}
*/		
	}

//==========================================================================================================================
//
//Controller Functions
//
//==========================================================================================================================
/*

	delete when new version is working

	void Controller::UpdateKeyboard(void) 
	{
		HRESULT result;

		result = _keyboard->GetDeviceState(sizeof(_keyboardState), (void*)&_keyboardState);
		
		if(FAILED(result)) 
		{
			if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) { _keyboard->Acquire(); }
			else { ErrorManager::Instance()->SetError(EC_DirectInput, "Failed to Get keyboard state, and failed to Re-Aquire"); }
		}					
	}

*/

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
	Controller::Controller(void)
	{	}

}//End namespace	