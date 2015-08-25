#include <Engine/ProgramWindow.h>

//========================================================================================================
//Constructors
//========================================================================================================
S32 ProgramWindow::_totalWidth      = 0;
S32 ProgramWindow::_totalHeight     = 0;
S32 ProgramWindow::_right			= 0;
S32 ProgramWindow::_left			= 0;
S32 ProgramWindow::_top				= 0;
S32 ProgramWindow::_bottom			= 0;

ProgramWindow::ProgramWindow(): _isFullScreen(false),
								_wndName("ProgramWindow"),
								_hwnd(NULL),
                                _hglrc(NULL),
                                _errorManager(ErrorManager::Instance()),
                                _controller(Controller::Instance())
{
	_totalWidth 	= 800;
	_totalHeight 	= 600;
	_right			= _totalWidth / 2;
    _left			= -_totalWidth / 2;
	_top			= _totalHeight / 2;
    _bottom			= -_totalHeight / 2;
    
	
    _errorManager->SetError(EC_OpenGL, "Called Default Constructor for ProgramWindow");
}

ProgramWindow::ProgramWindow(bool isFullScreen, S32 width, S32 height, text wndName):
	_isFullScreen(isFullScreen),
	_wndName(wndName),
	_hwnd(NULL),
    _hglrc(NULL),
    _errorManager(ErrorManager::Instance()),
    _controller(Controller::Instance())
{
    _totalWidth     = width;
    _totalHeight    = height;
    _right          = width / 2;
    _left           = -width / 2;
    _top            = height / 2;
    _bottom         = -height / 2;
}

//========================================================================================================
//Init Window
//========================================================================================================


void ProgramWindow::InitWindow(void) {
    //=========Window Class registration and creation===========
	_wndClass.cbSize        = sizeof(WNDCLASSEX);
    _wndClass.style 		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //Window Style
	_wndClass.lpfnWndProc   = &StaticWndProc; 	    //Windows Proc Callback function
	_wndClass.cbClsExtra    = 0;
    _wndClass.cbWndExtra    = 0;
	_wndClass.hInstance		= GetModuleHandle(NULL);//_hInstance;
    _wndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    _wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    _wndClass.hbrBackground = NULL;
	_wndClass.lpszMenuName  = NULL;
	_wndClass.lpszClassName = _wndName.c_str();
    _wndClass.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&_wndClass)) { _errorManager->SetError(EC_OpenGL, "Failed to register window class"); }

	_hwnd = CreateWindowEx(NULL,        //WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
				   		   _wndName.c_str(),					    //Window Class name
				   		   _wndName.c_str(),						//Window Name
				   		   WS_CLIPSIBLINGS 	   | WS_CLIPCHILDREN |  //Window Styles
				   		   WS_OVERLAPPEDWINDOW | WS_VISIBLE,		//^           ^
				   	  	   0,0,										//position of window
				   		   _totalWidth, _totalHeight,				//Dimensions
				   		   NULL, 									//Parent Window
				   		   NULL, 									//Window Menu
				   		   _wndClass.hInstance,						//hInstance,
				   		   this); 									//lpParam
	if (!_hwnd) { _errorManager->SetError(EC_OpenGL, "Failed to create HWND"); }

    _hdc = GetDC(_hwnd);

    if(!_hdc) { _errorManager->SetError(EC_OpenGL, "Failed to get HDC"); }

    ShowWindow(_hwnd, SW_SHOW);
    UpdateWindow(_hwnd);

    _controller->Init(_wndClass.hInstance, _hwnd);
}

//========================================================================================================
//ProcessWndEvents
//========================================================================================================
void ProgramWindow::ProcessWndEvents(void) {
    MSG msg;

    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

//========================================================================================================
//_SetTempPixelFormat
//========================================================================================================
void ProgramWindow::_SetTempPixelFormat(void) {
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

//========================================================================================================
//_SetPixelFormat
//========================================================================================================
void ProgramWindow::_SetPixelFormat(void) {
	bool worked = true;

    //PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionstextARB = NULL; 
    //wglGetExtensionstextARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionstextARB");
	//if (!wglGetExtensionstextARB){ worked = false; } //{ _errorManager->SetError(EC_OpenGL, "Unable to get wglGetExtensionstextARB function pointer"); }

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if (!wglChoosePixelFormatARB){ worked = false; } //{ _errorManager->SetError(EC_OpenGL, "Unable to get wglChoosePixelFormatARB function pointer"); }

    int pixCount    = 0;
    int pixelFormat = 0;

    int pixAtrb[] = {
        WGL_SUPPORT_OPENGL_ARB, 1, //Support OGL rendering
        WGL_DRAW_TO_WINDOW_ARB, 1, //pf that can run a window
        WGL_RED_BITS_ARB,       8, //8 bits of RGB color
        WGL_GREEN_BITS_ARB,     8,
        WGL_BLUE_BITS_ARB,      8,
        WGL_DEPTH_BITS_ARB,     16, //16 bits of depth
        WGL_ACCELERATION_ARB,
        WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,
        WGL_TYPE_RGBA_ARB,
        0};

    wglChoosePixelFormatARB(_hdc,              //device context
                            &pixAtrb[0],       //desired attributes
                            NULL,              //float attribute list
                            1,                 //max returned formats
                            &pixelFormat,      //list of returned formats
                            (UINT*)&pixCount); //number of formats found

    if(pixelFormat == -1) { _errorManager->SetError(EC_OpenGL, "Failed to load Pixel Format"); }

}

//========================================================================================================
//StaticWndProc
//========================================================================================================
LRESULT CALLBACK ProgramWindow::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	ProgramWindow* window = NULL;

    if(uMsg == WM_CREATE) {
        window = (ProgramWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;

        SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)window);
    }
    else {
        window = (ProgramWindow*)GetWindowLongPtr(hWnd, GWL_USERDATA);

		if (!window) { DefWindowProc(hWnd, uMsg, wParam, lParam); }
    }

    return window->WndProc(hWnd, uMsg, wParam, lParam);
}

//========================================================================================================
//WndProc
//========================================================================================================
LRESULT ProgramWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CREATE: {
			_hdc = GetDC(hWnd);
		    
			//=====Create temporary context=====
			_SetTempPixelFormat();            
            HGLRC hrcTemp = wglCreateContext(_hdc);
            wglMakeCurrent(_hdc, hrcTemp);

			//=====Create Real Context=====
            _SetPixelFormat();
            
			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
            if(!wglCreateContextAttribsARB) { _errorManager->SetError(EC_OpenGL, "Unable to get wglCreateContextAttribsARB function pointer"); }

            GLint contextARBS[] = 
            {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                WGL_CONTEXT_MINOR_VERSION_ARB, 2,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0
            };

            _hglrc = wglCreateContextAttribsARB(_hdc, 0, contextARBS);

            if(!_hglrc) { _errorManager->SetError(EC_OpenGL, "Failed to create wgl Context"); }

            wglMakeCurrent(_hdc, _hglrc);
            wglDeleteContext(hrcTemp);

            if (gl3wInit()) { _errorManager->SetError(EC_OpenGL, "gl3wInit() failed"); }

            return 0;
        }
        break;
        case WM_CLOSE: {
            _hdc = GetDC(hWnd);
            wglMakeCurrent(_hdc, NULL); 
			wglDeleteContext(_hglrc); 
			DestroyWindow(hWnd);
            PostQuitMessage(0);
            return 0;
        }
        break;
        case WM_SIZE: {
          /*  _width  = LOWORD(lParam);
            _height = HIWORD(lParam);
            
            _halfWidth  = _width / 2;
            _halfHeight = _height / 2;

            //_OnResize(); */
        }
        break;
        default:
            break;
    }
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}