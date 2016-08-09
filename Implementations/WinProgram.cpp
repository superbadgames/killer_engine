#include <Engine/WinProgram.h>

namespace KillerEngine {

//==========================================================================================================================
//
//Private WinProgram Functions
//
//==========================================================================================================================
//=======================================================================================================
//_SetTempPixelFormat
//=======================================================================================================
    void WinProgram::_SetTempPixelFormat(void) 
    {
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

//=======================================================================================================
//_SetPixelFormat
//=======================================================================================================
    void WinProgram::_SetPixelFormat(void) 
    {
        bool worked = true;

        //PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionstextARB = NULL; 
        //wglGetExtensionstextARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionstextARB");
        //if (!wglGetExtensionstextARB){ worked = false; } //{ _errorManager->SetError(EC_OpenGL, "Unable to get wglGetExtensionstextARB function Vecer"); }

        PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
        if (!wglChoosePixelFormatARB){ worked = false; } //{ _errorManager->SetError(EC_OpenGL, "Unable to get wglChoosePixelFormatARB function Vecer"); }

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

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
    S32 WinProgram::_totalWidth  = 0;
    S32 WinProgram::_totalHeight = 0;
    S32 WinProgram::_right       = 0;
    S32 WinProgram::_left        = 0;
    S32 WinProgram::_top         = 0;
    S32 WinProgram::_bottom      = 0;
    WinProgram::WinProgram(): _isFullScreen(false),
    								_wndName("WinProgram"),
    								_hwnd(NULL),
                                    _hglrc(NULL),
                                    _errorManager(ErrorManager::Instance()),
                                    _controller(Controller::Instance())
    {
    	
    }
//==========================================================================================================================
//
//WinProgram Functions
//
//==========================================================================================================================
//=======================================================================================================
//Instance
//=======================================================================================================
    WinProgram* WinProgram::_instance = NULL;

    WinProgram* WinProgram::Instance(void) 
    {
        if(_instance == NULL) { _instance = new WinProgram; }
        return _instance;
    }

//=======================================================================================================
//InitWindow
//=======================================================================================================    
    void WinProgram::Init(S32 width, S32 height, string wndName, bool isFullScreen) 
    {
        _totalWidth     = width;
        _totalHeight    = height;
        _right          = _totalWidth / 2;
        _left           = -_totalWidth / 2;
        _top            = _totalHeight / 2;
        _bottom         = -_totalHeight / 2;

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

        //_controller->Init(_wndClass.hInstance, _hwnd);
    }

//=======================================================================================================
//ProcessWndEvents
//=======================================================================================================
    void WinProgram::ProcessWndEvents(void) 
    {
        MSG msg;

        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

//=======================================================================================================
//BufferSwap
//=======================================================================================================
    void WinProgram::BufferSwap(void)
    { 
        glFlush(); 
        SwapBuffers(_hdc); 
        glClearBufferfv(GL_COLOR, 0, _bgColor);
    }
//==========================================================================================================================
//
//System Windows Functions
//
//==========================================================================================================================
//=======================================================================================================
//StaticWndProc
//=======================================================================================================    
    LRESULT CALLBACK WinProgram::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
    {
    	WinProgram* window = NULL;

        if(uMsg == WM_CREATE) 
        {
            window = (WinProgram*)((LPCREATESTRUCT)lParam)->lpCreateParams;

            SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)window);
        }
        else 
        {
            window = (WinProgram*)GetWindowLongPtr(hWnd, GWL_USERDATA);

    		if (!window) { DefWindowProc(hWnd, uMsg, wParam, lParam); }
        }

        return window->WndProc(hWnd, uMsg, wParam, lParam);
    }

//=======================================================================================================
//WndProc
//=======================================================================================================    
    LRESULT WinProgram::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
    {
        switch(uMsg) 
        {
            case WM_CREATE: 
            {
    			_hdc = GetDC(hWnd);
    		    
    			//=====Create temporary context=====
    			_SetTempPixelFormat();            
                HGLRC hrcTemp = wglCreateContext(_hdc);
                wglMakeCurrent(_hdc, hrcTemp);

    			//=====Create Real Context=====
                _SetPixelFormat();
                
    			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
                wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
                if(!wglCreateContextAttribsARB) { _errorManager->SetError(EC_OpenGL, "Unable to get wglCreateContextAttribsARB function Vecer"); }

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

                break;
            }
            case WM_DESTROY: 
            {
                _hdc = GetDC(hWnd);
                wglMakeCurrent(_hdc, NULL); 
    			wglDeleteContext(_hglrc); 
    			DestroyWindow(hWnd);
                PostQuitMessage(0);
                break;
            }
            //case WM_SIZE: {
              /*  _width  = LOWORD(lParam);
                _height = HIWORD(lParam);
                
                _halfWidth  = _width / 2;
                _halfHeight = _height / 2;

                //_OnResize(); */
            //}
            //break;
            case WM_KEYDOWN:
            {
                Keys keydown = ConvertKeyCodes(wParam);
                Controller::Instance()->KeyPress(keydown);
                break;
            }
            case WM_KEYUP:
            {
                Keys keyup = ConvertKeyCodes(wParam);
                Controller::Instance()->KeyRelease(keyup);
                break;
            }
            default:
            	return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    	return 0;
    }

    Keys WinProgram::ConvertKeyCodes(WPARAM wParam)
    {
        switch(wParam)
        {
            case 'A':
                return Keys::A_KEY;
            case 'B':
                return Keys::B_KEY;
            case 'C':
                return Keys::C_KEY;
            case 'D':
                return Keys::D_KEY;
            case 'E':
                return Keys::E_KEY;
            case 'F':
                return Keys::F_KEY;
            case 'G':
                return Keys::G_KEY;
            case 'H':
                return Keys::H_KEY;
            case 'I':
                return Keys::I_KEY;
            case 'J':
                return Keys::J_KEY;
            case 'K':
                return Keys::K_KEY;    
            case 'L':
                return Keys::L_KEY;
            case 'M':
                return Keys::M_KEY;
            case 'N':
                return Keys::N_KEY;
            case 'O':
                return Keys::O_KEY;
            case 'P':
                return Keys::P_KEY;
            case 'Q':
                return Keys::Q_KEY;
            case 'R':
                return Keys::R_KEY;
            case 'S':
                return Keys::S_KEY;
            case 'T':
                return Keys::T_KEY;
            case 'U':
                return Keys::U_KEY;
            case 'V':
                return Keys::V_KEY;
            case 'X':
                return Keys::X_KEY;
            case 'Y':
                return Keys::Y_KEY;
            case 'Z':
                return Keys::Z_KEY;
            case VK_UP:
                return Keys::UP_ARROW;
            case VK_DOWN:
                return Keys::DOWN_ARROW;
            case VK_LEFT:
                return Keys::LEFT_ARROW;
            case VK_RIGHT:
                return Keys::RIGHT_ARROW;
            case '0':
                return Keys::ZERO_KEY;
            case '1':
                return Keys::ONE_KEY;
            case '2':
                return Keys::TWO_KEY;
            case '3':
                return Keys::THREE_KEY;
            case '4':
                return Keys::FOUR_KEY;
            case '5':
                return Keys::FIVE_KEY;
            case '6':
                return Keys::SIX_KEY;
            case '7':
                return Keys::SEVEN_KEY;
            case '8':
                return Keys::EIGHT_KEY;
            case '9':
                return Keys::NINE_KEY;
            case VK_OEM_MINUS:
                return Keys::MINUS_KEY;
            case VK_OEM_PLUS:
                return Keys::PLUS_KEY;
            case VK_SPACE:
                return Keys::SPACEBAR_KEY;
            case VK_ESCAPE:
                return Keys::ESCAPE_KEY;
            case VK_TAB:
                return Keys::TAB_KEY;
            case VK_LSHIFT:
                return Keys::LSHIFT_KEY;
            case VK_RSHIFT:
                return Keys::RSHIFT_KEY;
            case VK_RETURN:
                return Keys::ENTER_KEY;
            case VK_RBUTTON:
                return Keys::RIGHT_MOUSE;
            case VK_LBUTTON:
                return Keys::LEFT_MOUSE;
            case VK_XBUTTON1:
                return Keys::MIDDLE_MOUSE;
            default:
                return Keys::NO_KEY;
        }
    }

}//End namespace    