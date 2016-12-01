/*========================================================================
Human input device controller. Abstract Keyboard input is received through
a system all found in the *Program class. 

For example, in WinProgram, when windows gets a key input message for a
key down even, KeyDown(Keys k) is called.

Two enums are defined. 

KeyStates represents all the possible states that
a key can have. KEY_RELEASED  means that the key is not pressed. KEY_UP 
means that the key was released this frame. 

Keys represents all the supported keys. 

Update handles the logic of changing they key states, with two KeyState 
arrays holding the current key states, that is the key states of this frame
and the past key states, that is the key states from last frame.

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
#include <Engine/Matrix.hpp>
namespace KM = KillerMath;


//=====DirectInput includes=====
//#include <dinput.h>

namespace KillerEngine 
{
	enum KeyStates
	{
		KEY_DOWN = 1,
		KEY_HELD,
		KEY_UP,
		KEY_RELEASED
	};

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
	public:
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static Controller* Instance();
		 
		void ShutDown(void);

//==========================================================================================================================
//
//Controller Functions
//
//==========================================================================================================================
		void Update(void);

		void Init(F32 w, F32 h, F32 d) { _transform.MakeOrthographic(w, h, d); }

		void KeyDown(Keys k) { _curActiveKeys[k] = true; }

		void KeyUp(Keys k) { _curActiveKeys[k] = false; }

		void LeftMouseClick(Vec2 coord) { _leftClickCoordinates = coord; }

		Vec2 GetLeftMouseCoord(void) { return _leftClickCoordinates; }

		void RightMouseClick(Vec2 coord) { _rightClickCoordinates = coord; }

		Vec2 GetRightMouseCoord(void) { return _rightClickCoordinates; }

		//KeyState GetKeyState(Keys k) { return _curKeyStates[k]; }

		bool GetKeyDown(Keys k);

		bool GetKeyHeld(Keys k);

		bool GetKeyUp(Keys k);

		bool GetKeyReleased(Keys k);

		Controller* operator =(Controller& c) { return &c; }

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		explicit Controller(void);		

	private:
		static const int 		_totalKeys = 51;
		KeyStates   			_keyStates[_totalKeys];
		bool 					_pastActiveKeys[_totalKeys];
		bool					_curActiveKeys[_totalKeys];
		Vec2 					_leftClickCoordinates;
		Vec2					_rightClickCoordinates;
		static Controller*   	_instance;
		KM::Matrix4<F32>		_transform;
	};
}//End namespace

#endif