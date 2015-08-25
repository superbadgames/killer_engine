/*========================================================================
Human input device controller. Will use SDL to poll input from the key-
board and any other controller devices.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef CONTROLLER_H
#define CONTROLLER_H
#define DIRECTINPUT_VERSION 0x0800

//Engine includes
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vector.hpp>

//3rd party includes
#include <dinput.h>

class Controller {
private:
	IDirectInput8*    	 _directInput;
	IDirectInputDevice8* _keyboard;
	unsigned char 		 _keyboardState[256];

	static Controller* _instance;
	ErrorManager* _errorManager;


protected:
	explicit Controller(void);


public:
	static Controller* Instance();

	 void Init(HINSTANCE hInstance, HWND hwnd);
	 void ShutDown(void);

	void UpdateKeyboard(void);

	unsigned char* GetKeyboardState(void);

	Controller* operator =(Controller& c) {
		return &c;
	}
};


#endif