/*========================================================================
Human input device controller. Will use SDL to poll input from the key-
board and any other controller devices.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef CONTROLLER_H
#define CONTROLLER_H
//#define DIRECTINPUT_VERSION 0x0800

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>


//=====DirectInput includes=====
//#include <dinput.h>

namespace KillerEngine 
{
	enum Keys 
	{
		NO_KEY=0,
		A=1,
		B=2,
		C=3,
		D=4,
		E=5,
		F=6,
		G=7,
		H=8,
		I=9,
		J=10,
		K=11,
		L=12,
		M=13,
		N=14,
		O=15,
		P=16,
		Q=17,
		R=18,
		S=19,
		T=20,
		U=21,
		V=22,
		W=23,
		X=24,
		Y=25,
		Z=26,
		UP_ARROW=27,
		DOWN_ARROW=28,
		LEFT_ARROW=29,
		RIGHT_ARROW=30,
		ZERO=31,
		ONE=32,
		TWO=33,
		THREE=34,
		FOUR=35,
		FIVE=36,
		SIX=37,
		SEVEN=38,
		EIGHT=39,
		NINE=40,
		MINUS=41,
		PLUS=42,
		SPACE=43,
		ESCAPE=44,
		TAB=45,
		LSHIFT=46,
		RSHIFT=47,
		ENTER=48,
		RIGHT_MOUSE=49,
		LEFT_MOUSE=50,
		MIDDLE_MOUSE=51,
	};
	
	class Controller 
	{
	private:
		//IDirectInput8*    	_directInput;
		//IDirectInputDevice8*  _keyboard;
		//unsigned char 		_keyboardState[256];
		bool   					_activeKeys[51];
		static Controller*   	_instance;
		

	public:
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static Controller* Instance();

		//void Init(HINSTANCE hInstance, HWND hwnd);


		 
		void ShutDown(void);

//==========================================================================================================================
//
//Controller Functions
//
//==========================================================================================================================
		//void UpdateKeyboard(void);

		void KeyDown(Keys k);

		void KeyUp(Keys k);

		//bool GetKeyboardState(void) { return _activeKeys; }

		bool GetKeyState(Keys k) { return _activeKeys[k]; }

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