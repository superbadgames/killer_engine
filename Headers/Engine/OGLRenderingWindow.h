/*==========================================================================
The OGLRenderingWindow is where the OGL window is opened, and set up. It
will also control the windows messages for resizing, and focus. This should 
not be called outside of the program start up.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
===========================================================================*/

#ifndef GL_WINDOW_H
#define GL_WINDOW_H

//=========user defined includes=========
#include <Atom.h>
#include <Timer.h>
#include <ErrorManager.h>

//=========3rd Party includes==========
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <wglext.h>

class OGLRenderingWindow {
private:
	bool 	  _isRunning;
	bool 	  _isFullScreen;
	
	static S32 _width;
	static S32 _height;
	static S32 _halfWidth;
	static S32 _halfHeight;

	Timer*    	  _timer;
	ErrorManager* _errorManager;

	HWND       _hwnd;
	HGLRC      _hglrc; //Rendering context
	HDC 	   _hdc;
	RECT 	   _windowRect;
	HINSTANCE  _hInstance;
	WNDCLASSEX _windowClass;

	void _OnResize(void);
	void _SetupPixelFormat(void);
	void _SetProjectionMatrix(void);

public:
	OGLRenderingWindow(HINSTANCE hInstance);//Default constructor
	
	void Init(S32 width, S32 height, S32 bpp, bool fullscreen);
	void ShutDown(void);
	void ProcessEvents(void);

	bool isRunning(void) { return _isRunning; }

	void Swap(void) { SwapBuffers(_hdc); }

	static LRESULT CALLBACK StaticWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	float GetElapsedSeconds();

	HWND GetHWND(void) { return _hwnd; }

	static S32 GetWidth     (void)  { return _width; }
	static S32 GetHalfWidth (void)  { return _halfWidth; }
	static S32 GetHeight    (void) 	{ return _height; }
	static S32 GetHalfHeight(void)  { return _halfHeight; }

};

#endif