/*==========================================================================
Framework that will open a window in the designated operating system which
will be where the renderer will draw what it needs to for the game to be a
game. There will be system specific code in this section which will be how
the game will run on each system that is supported. 

Supported system:
	Windows


This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
===========================================================================*/
#ifndef PROGRAM_WINDOW_H
#define PROGRAM_WINDOW_H

//==========User defined includes==========
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Controller.h>

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

class ProgramWindow{
private:
	bool _isFullScreen;
	static S32  _totalWidth;
	static S32  _totalHeight;
	static S32  _right;
	static S32  _left;
	static S32  _top;
	static S32  _bottom;
	text _wndName;

	ErrorManager* _errorManager;
	Controller* _controller;

	//=====Windows Variables=====
	HWND _hwnd;
	HDC _hdc;
	HGLRC _hglrc;
	WNDCLASSEX _wndClass;

	void _SetTempPixelFormat(void);
	void _SetPixelFormat(void);
	
public:
	ProgramWindow(void);
	ProgramWindow(bool isFullScreen, S32 width, S32 height, text wndName);
	~ProgramWindow(void) {  }

	void InitWindow(void);
	void ProcessWndEvents(void);
	void BufferSwap(void) { glFlush(); SwapBuffers(_hdc); }
	
	static LRESULT CALLBACK StaticWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND      GetHWND(void)      { return _hwnd; }
	HINSTANCE GetHINSTANCE(void) { return _wndClass.hInstance; }
	
	static S32 GetWidth(void)	   { return _totalWidth; }
	static S32 GetHalfWidth(void)  { return _right; }
	static S32 GetRight(void) 		{ return _right; }
	static S32 GetLeft(void)		{ return _left; }
	static S32 GetHeight(void) 	   { return _totalHeight; }
	static S32 GetHalfHeight(void) { return _top; }
	static S32 GetTop(void) 		{ return _top; }
	static S32 GetBottom(void) 		{ return _bottom; }
};

#endif