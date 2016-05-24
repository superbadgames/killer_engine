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

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vector.hpp>

//=====DirectInput includes=====
#include <dinput.h>

namespace KillerEngine 
{
	
	class Controller 
	{
	private:
		IDirectInput8*    	 _directInput;
		IDirectInputDevice8* _keyboard;
		unsigned char 		 _keyboardState[256];
		static Controller*   _instance;
		ErrorManager* 		 _errorManager;

	public:
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static Controller* Instance();

		 void Init(HINSTANCE hInstance, HWND hwnd);
		 
		 void ShutDown(void);

//==========================================================================================================================
//
//Controller Functions
//
//==========================================================================================================================
		void UpdateKeyboard(void);

		unsigned char* GetKeyboardState(void) { return _keyboardState; }

		Controller* operator =(Controller& c) { return &c; }

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		explicit Controller(void);		
	};
}//End namespace

#endif