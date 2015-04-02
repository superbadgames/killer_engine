#include <OGLRenderingWindow.h>

//-------------------------------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------------------------------
OGLRenderingWindow::OGLRenderingWindow(HINSTANCE hInstance): _isRunning(false),
                                                             _hInstance(hInstance) { 
                                                             _timer->Instance(); 
}


//-------------------------------------------------------------------------------------------------------
//Init
//-------------------------------------------------------------------------------------------------------
bool OGLRenderingWindow::Init(S32 width, S32 height, S32 bpp, bool fullscreen) {
    DWORD dwExStyle;
    DWORD dwStyle;

	_width  = width;
	_height = height;

    _halfWidth = width / 2;
    _halfHeight = height / 2;
    
	_isFullScreen = fullscreen;

    _windowRect.left   = (S64)0;
    _windowRect.right  = (S64)width;
    _windowRect.top    = (S64)0;
    _windowRect.bottom = (S64)height;

    //Fill out window call struct
    _windowClass.cbSize        = sizeof(WNDCLASSEX);
    _windowClass.style         = CS_HREDRAW | CS_VREDRAW;
    _windowClass.lpfnWndProc   = OGLRenderingWindow::StaticWndProc; //Event handler
    _windowClass.cbClsExtra    = 0;
    _windowClass.cbWndExtra    = 0;
    _windowClass.hInstance     = _hInstance;
    _windowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    _windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	_windowClass.hbrBackground = NULL;
    _windowClass.lpszMenuName  = NULL;
    _windowClass.lpszClassName = "GLClass";
    _windowClass.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);

    //Register the windows class
	if (!RegisterClassEx(&_windowClass)) {
        MessageBox(NULL, "Failed to register window class", NULL, MB_OK);
        return false;
    }

    if(_isFullScreen) {
        DEVMODE dmScreenSettings;

        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);

        dmScreenSettings.dmPelsWidth    = width;
        dmScreenSettings.dmPelsHeight   = height;
        dmScreenSettings.dmBitsPerPel   = bpp;
        dmScreenSettings.dmFields       = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
            //Setting mode failed, switch to windowed
            MessageBox(NULL, "Display mode failed", NULL, MB_OK);
            _isFullScreen = false;
        }
    }

    if(_isFullScreen) {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle   = WS_POPUP;
        ShowCursor(false);
    }
    else {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle   = WS_OVERLAPPEDWINDOW;
    }

    AdjustWindowRectEx(&_windowRect, dwStyle, false, dwExStyle);

    _hwnd = CreateWindowEx(NULL,                                       //extended style
                            "GLClass",                                  //class name
                            "Boxes",    //app name
							dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                            0, 0,                                       //X, Y
                            _windowRect.right - _windowRect.left,
                            _windowRect.bottom - _windowRect.top,     //height and width
                            NULL,                                       //handle to parent
                            NULL,                                       //handle to menu
                            _hInstance,                                //application instance
                            this);                                      //pointer to OGLRenderingWindow

    if(!_hwnd) { return 0; }

    _hdc = GetDC(_hwnd);

    ShowWindow(_hwnd, SW_SHOW);
    UpdateWindow(_hwnd);

    _SetProjectionMatrix();


    return true;
}

//-------------------------------------------------------------------------------------------------------
//ShutDown
//-------------------------------------------------------------------------------------------------------
void OGLRenderingWindow::ShutDown() {
    if(_isFullScreen) {
        ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
    }
}

//-------------------------------------------------------------------------------------------------------
//StaticWndProc
//-------------------------------------------------------------------------------------------------------
LRESULT CALLBACK OGLRenderingWindow::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	OGLRenderingWindow* window = NULL;

    if(uMsg == WM_CREATE) {
        window = (OGLRenderingWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;

        SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)window);
    }
    else {
        window = (OGLRenderingWindow*)GetWindowLongPtr(hWnd, GWL_USERDATA);

		if (!window) { DefWindowProc(hWnd, uMsg, wParam, lParam); }
    }

    return window->WndProc(hWnd, uMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------------
//WndProc
//-------------------------------------------------------------------------------------------------------
LRESULT OGLRenderingWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CREATE: {
            _hdc = GetDC(hWnd);
            _SetupPixelFormat();

			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

            S32 attribs[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                             WGL_CONTEXT_MINOR_VERSION_ARB, 0,
                             0};

            HGLRC tmpContext = wglCreateContext(_hdc);
            wglMakeCurrent(_hdc, tmpContext);

            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

            if(!wglCreateContextAttribsARB) {
                MessageBox(NULL, "OpenGL 3.0 is not supported", "An error occured", MB_ICONERROR | MB_OK);
                DestroyWindow(hWnd);
                return 0;
            }

            _hglrc = wglCreateContextAttribsARB(_hdc, 0, attribs);
           // wglDeleteContext(tmpContext);
            wglMakeCurrent(_hdc, _hglrc);

            _isRunning = true;
        }
		break;
        
        case WM_DESTROY:
        case WM_CLOSE: {
            wglMakeCurrent(_hdc, NULL);
            wglDeleteContext(_hglrc);
            _isRunning = false;
            PostQuitMessage(0);
            return 0;
        }
        break;
        case WM_SIZE: {
            _width  = LOWORD(lParam);
            _height = HIWORD(lParam);
            
            _halfWidth  = _width / 2;
            _halfHeight = _height / 2;

            _OnResize();
        }
        break;
        case WM_KEYDOWN: {
            if(wParam == VK_ESCAPE) { DestroyWindow(_hwnd); }
        }
        break;
        default:
            break;
    }
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//-------------------------------------------------------------------------------------------------------
//ProcessEvents
//-------------------------------------------------------------------------------------------------------
void OGLRenderingWindow::ProcessEvents() {
    MSG msg;

    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


//-------------------------------------------------------------------------------------------------------
//_SetupPixelFormat
//-------------------------------------------------------------------------------------------------------
void OGLRenderingWindow::_SetupPixelFormat(void) {
    S32 pixelFormat;

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),  //size
        1,                              //version
        PFD_SUPPORT_OPENGL |            //OpenGL window
        PFD_DRAW_TO_WINDOW |            //render to window
        PFD_DOUBLEBUFFER,               //support double buffer
        PFD_TYPE_RGBA,                  //color type
        32,                             //prefered color depth
        0,0,0,0,0,0,                    //color bits (ignored)
        0,                              //no alpha buffer
        0,                              //alpha bits ignored
        0,                              //no accumulation buffer
        0,0,0,0,                        //accum bits (ignored)
        16,                             //depth buffer
        0,                              //no stencil buffer
        0,                              //no aux buffers
        PFD_MAIN_PLANE,                 //main layer
        0,                              //reserved
        0,0,0                           //no layer, visible, damage masks

    };

    pixelFormat = ChoosePixelFormat(_hdc, &pfd);
    SetPixelFormat(_hdc, pixelFormat, &pfd);
}

//-------------------------------------------------------------------------------------------------------
//_SetProjectionMatrix
//-------------------------------------------------------------------------------------------------------
void OGLRenderingWindow::_SetProjectionMatrix(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-_halfWidth, _halfWidth, -_halfHeight, _halfHeight, -100, 100 );
    glMatrixMode(GL_MODELVIEW);

	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
}

//-------------------------------------------------------------------------------------------------------
//_OnResize
//-------------------------------------------------------------------------------------------------------
void OGLRenderingWindow::_OnResize(void) {
	glViewport(0, 0, _width, _height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, F32(_width) / F32(_height), 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    _SetProjectionMatrix();
}