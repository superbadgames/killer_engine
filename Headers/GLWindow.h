#ifndef GL_WINDOW_H
#define GL_WINDOW_H

//user defined includes
#include <Atom.h>
#include <Example.h>

//3rd Party includes
#include <windows.h>
#include <ctime>
#include <iostream>
#include <GL/gl.h>
#include <wglext.h>

//#include <glext.h>
//PFNGLUSEPROGRAMPROC wglCreateContextAttribsARB = NULL;

//typedef HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
//PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

//typedef GLXContext(*PFNGLXCREATECONTEXTATTRIBSARBPROC) (Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);
//PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;



class Example;

class GLWindow {
public:
	GLWindow(HINSTANCE hInstance);//Default constructor
	
	bool Create(S32 width, S32 height, S32 bpp, bool fullscreen);
	void Destroy();
	void ProcessEvents();
	void AttachExample(Example* example) { m_example = example; }

	bool isRunning() { return m_isRunning; }

	void MySwapBuffers() { SwapBuffers(m_hdc); }

	static LRESULT CALLBACK StaticWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	float GetElapsedSeconds();

private:
	Example* m_example;
	bool 	 m_isRunning;
	bool 	 m_isFullScreen;
	float 	 m_lastTime;

	HWND       m_hwnd;
	HGLRC      m_hglrc; //Rendering context
	HDC 	   m_hdc;
	RECT 	   m_windowRect;
	HINSTANCE  m_hInstance;
	WNDCLASSEX m_windowClass;

	//HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, contst int *attribList);

	void SetupPixelFormat(void);
	Example* GetAttachedExample() { return m_example; }
};

#endif