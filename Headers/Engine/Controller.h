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
		A_KEY=1,
		B_KEY=2,
		C_KEY=3,
		D_KEY=4,
		E_KEY=5,
		F_KEY=6,
		G_KEY=7,
		H_KEY=8,
		I_KEY=9,
		J_KEY=10,
		K_KEY=11,
		L_KEY=12,
		M_KEY=13,
		N_KEY=14,
		O_KEY=15,
		P_KEY=16,
		Q_KEY=17,
		R_KEY=18,
		S_KEY=19,
		T_KEY=20,
		U_KEY=21,
		V_KEY=22,
		W_KEY=23,
		X_KEY=24,
		Y_KEY=25,
		Z_KEY=26,
		UP_ARROW=27,
		DOWN_ARROW=28,
		LEFT_ARROW=29,
		RIGHT_ARROW=30,
		ZERO_KEY=31,
		ONE_KEY=32,
		TWO_KEY=33,
		THREE_KEY=34,
		FOUR_KEY=35,
		FIVE_KEY=36,
		SIX_KEY=37,
		SEVEN_KEY=38,
		EIGHT_KEY=39,
		NINE_KEY=40,
		MINUS_KEY=41,
		PLUS_KEY=42,
		SPACEBAR_KEY=43,
		ESCAPE_KEY=44,
		TAB_KEY=45,
		LSHIFT_KEY=46,
		RSHIFT_KEY=47,
		ENTER_KEY=48,
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