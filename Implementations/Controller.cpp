#include <Engine/Controller.h>

//-----------------------------------------------------------
//Constructor
//-----------------------------------------------------------
Controller::Controller(void) {
	_errorManager->Instance();

	_directInput = 0;
	_keyboard    = 0;
}

//-----------------------------------------------------------
//Instance
//-----------------------------------------------------------
Controller* Controller::_instance = NULL;

Controller* Controller::Instance(void) {
	if (_instance == NULL) { _instance = new Controller(); }
	return _instance;
}

//-----------------------------------------------------------
//Init
//-----------------------------------------------------------
void Controller::Init(HINSTANCE hInstance, HWND hwnd) {
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

//-----------------------------------------------------------
//ShutDown
//-----------------------------------------------------------
void Controller::ShutDown(void) {
	if(_keyboard) {
		_keyboard->Unacquire();
		_keyboard->Release();
		_keyboard = 0;
	}
}

//-----------------------------------------------------------
//UpdateInput
//-----------------------------------------------------------
void Controller::UpdateKeyboard(void) {
	HRESULT result;

	result = _keyboard->GetDeviceState(sizeof(_keyboardState), (void*)&_keyboardState);
	if(FAILED(result)) {
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) { _keyboard->Acquire(); }
		else { _errorManager->SetError(EC_DirectInput, "Failed to Get keyboard state, and failed to Re-Aquire"); }
	}					
}

unsigned char* Controller::GetKeyboardState(void) {
	return _keyboardState;
}