#include <Controller.h>

//-----------------------------------------------------------
//Constructor
//-----------------------------------------------------------
Controller::Controller(void) {
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
bool Controller::Init(HINSTANCE hInstance, HWND hwnd) {
	HRESULT result;

	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_directInput, NULL);
	if(FAILED(result)) { return false; }

	result = _directInput->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL);
	if(FAILED(result)) { return false; }

	result = _keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(result)) { return false; }

	result = _keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result)) { return false; }

	result = _keyboard->Acquire();
	if(FAILED(result)) { return false; }

	return true;

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
bool Controller::UpdateKeyboard(void) {
	HRESULT result;

	result = _keyboard->GetDeviceState(sizeof(_keyboardState), (void*)&_keyboardState);
	if(FAILED(result)) {
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) { _keyboard->Acquire(); }
		else {
			MessageBox(NULL, "Unable to get Keyboard input", "An Error occured", MB_ICONERROR | MB_OK);
			return false;
		}
		
	}
	return true;	
					
}

unsigned char* Controller::ProcessInput(void) {
	return _keyboardState;
	
	/*if(_keyboardState[DIK_UP])	    { return 'u'; }
	if (_keyboardState[DIK_DOWN])   { return 'd'; }
	if (_keyboardState[DIK_RIGHT])  { return  'r'; }
	if (_keyboardState[DIK_LEFT])   { return 'l'; }
	return 'p';*/
	//else return ;
}