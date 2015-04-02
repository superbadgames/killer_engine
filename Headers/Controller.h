/*--------------------------------------------------------------------
Human input device controller. Will use SDL to poll input from the key-
board and any other controller devices.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
----------------------------------------------------------------------*/
#ifndef CONTROLLER_H
#define CONTROLLER_H

//Engine includes
#include <Atom.h>
#include <Vector.hpp>

//3rd party includes
#include <dinput.h>
#include <string>

class Controller {
private:
	IDirectInput8*    	 _directInput;
	IDirectInputDevice8* _keyboard;
	unsigned char 		 _keyboardState[256];

	static Controller* _instance;
	//bool _ReadKeyboard(void);


protected:
	explicit Controller(void);


public:
	static Controller* Instance();

	 bool Init(HINSTANCE hInstance, HWND hwnd);
	 void ShutDown(void);

	bool UpdateKeyboard(void);

	unsigned char* ProcessInput(void);

	Controller* operator =(Controller& c) {
		return &c;
	}
};


#endif