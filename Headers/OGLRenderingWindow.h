#ifndef GL_WINDOW_H
#define GL_WINDOW_H

//user defined includes
#include <Atom.h>
#include <Renderer.h>

//3rd Party includes
//#include <ctime>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <wglext.h>


class OGLRenderingWindow {
public:
	OGLRenderingWindow(HINSTANCE hInstance);//Default constructor
	
	bool Create(S32 width, S32 height, S32 bpp, bool fullscreen);
	void Destroy();
	void ProcessEvents();

	bool isRunning() { return _isRunning; }

	void MySwapBuffers() { SwapBuffers(_hdc); }

	static LRESULT CALLBACK StaticWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	float GetElapsedSeconds();

private:
	bool 	 _isRunning;
	bool 	 _isFullScreen;
	float 	 _lastTime;
	S32		 _width;
	S32		 _height;

	HWND       _hwnd;
	HGLRC      _hglrc; //Rendering context
	HDC 	   _hdc;
	RECT 	   _windowRect;
	HINSTANCE  _hInstance;
	WNDCLASSEX _windowClass;

	//HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, contst int *attribList);

	void _OnResize(S32 width, S32 height);
	void _SetupPixelFormat(void);
};

#endif