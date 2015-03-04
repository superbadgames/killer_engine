#include <GLWindow.h>

//typedef HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
//PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

//-----------------------------------------------Default constructor
GLWindow::GLWindow(HINSTANCE hInstance):
m_isRunning(false),
m_example(NULL),
m_hInstance(hInstance),
m_lastTime(0) {}


//----------------------------------------------------------------------------Create
bool GLWindow::Create(S32 width, S32 height, S32 bpp, bool fullscreen) {
    DWORD dwExStyle;
    DWORD dwStyle;

    m_isFullScreen = fullscreen;

    m_windowRect.left   = (S64)0;
    m_windowRect.right  = (S64)width;
    m_windowRect.top    = (S64)0;
    m_windowRect.bottom = (S64)height;

    //Fill out window call struct
    m_windowClass.cbSize        = sizeof(WNDCLASSEX);
    m_windowClass.style         = CS_HREDRAW | CS_VREDRAW;
    m_windowClass.lpfnWndProc   = GLWindow::StaticWndProc; //Event handler
    m_windowClass.cbClsExtra    = 0;
    m_windowClass.cbWndExtra    = 0;
    m_windowClass.hInstance     = m_hInstance;
    m_windowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    m_windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	m_windowClass.hbrBackground = NULL;
    m_windowClass.lpszMenuName  = NULL;
    m_windowClass.lpszClassName = "GLClass";
    m_windowClass.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);

    //Register the windows class
	if (!RegisterClassEx(&m_windowClass)) {
        MessageBox(NULL, "Failed to register window class", NULL, MB_OK);
        return false;
    }

    if(m_isFullScreen) {
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
            m_isFullScreen = false;
        }
    }

    if(m_isFullScreen) {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle   = WS_POPUP;
        ShowCursor(false);
    }
    else {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle   = WS_OVERLAPPEDWINDOW;
    }

    AdjustWindowRectEx(&m_windowRect, dwStyle, false, dwExStyle);

    m_hwnd = CreateWindowEx(NULL,                                       //extended style
                            "GLClass",                                  //class name
                            "BOGLGP - Chapter 2 OpenGL Application",    //app name
							dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                            0, 0,                                       //X, Y
                            m_windowRect.right - m_windowRect.left,
                            m_windowRect.bottom - m_windowRect.top,     //height and width
                            NULL,                                       //handle to parent
                            NULL,                                       //handle to menu
                            m_hInstance,                                //application instance
                            this);                                      //pointer to GLWindow

    if(!m_hwnd) { return 0; }

    m_hdc = GetDC(m_hwnd);

    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);

	m_lastTime = GetTickCount() / 1000.0f; //Initialize the timer
    return true;
}

//-----------------------------------------------------------------------------Destroy
void GLWindow::Destroy() {
    if(m_isFullScreen) {
        ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
    }
}

//----------------------------------------------------------------------------------------------StaticWndProc
LRESULT CALLBACK GLWindow::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	GLWindow* window = NULL;

    if(uMsg == WM_CREATE) {
        window = (GLWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;

        SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)window);
    }
    else {
        window = (GLWindow*)GetWindowLongPtr(hWnd, GWL_USERDATA);

		if (!window) { DefWindowProc(hWnd, uMsg, wParam, lParam); }
    }

    return window->WndProc(hWnd, uMsg, wParam, lParam);
}

//------------------------------------------------------------------------------WndProc
LRESULT GLWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CREATE: {
            m_hdc = GetDC(hWnd);
            SetupPixelFormat();

			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

            int attribs[] = {WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                             WGL_CONTEXT_MINOR_VERSION_ARB, 0,
                             0};

            HGLRC tmpContext = wglCreateContext(m_hdc);
            wglMakeCurrent(m_hdc, tmpContext);

            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

            if(!wglCreateContextAttribsARB) {
                MessageBox(NULL, "OpenGL 3.0 is not supported", "An error occured", MB_ICONERROR | MB_OK);
                DestroyWindow(hWnd);
                return 0;
            }

            m_hglrc = wglCreateContextAttribsARB(m_hdc, 0, attribs);
           // wglDeleteContext(tmpContext);
            wglMakeCurrent(m_hdc, m_hglrc);

            m_isRunning = true;
        }
		break;
        
        case WM_DESTROY:
        case WM_CLOSE: {
            wglMakeCurrent(m_hdc, NULL);
            wglDeleteContext(m_hglrc);
            m_isRunning = false;
            PostQuitMessage(0);
            return 0;
        }
        break;
        case WM_SIZE: {
            int height = HIWORD(lParam);
            int width  = LOWORD(lParam);
            GetAttachedExample()->OnResize(width, height);
        }
        break;
        case WM_KEYDOWN: {
            if(wParam == VK_ESCAPE) { DestroyWindow(m_hwnd); }
        }
        break;
        default:
            break;
    }
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//-------------------------------------------------------------------ProcessEvents
void GLWindow::ProcessEvents() {
    MSG msg;

    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

//-----------------------------------------------------------------GetElapsedSeconds
float GLWindow::GetElapsedSeconds(){
    float currentTime = float(GetTickCount()) / 1000.0f;
    float seconds = float(currentTime - m_lastTime);
    m_lastTime = currentTime;
    return seconds;
}

//--------------------------------------------------------------------------SetupPixelFormat
void GLWindow::SetupPixelFormat(void) {
    int pixelFormat;

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

    pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
    SetPixelFormat(m_hdc, pixelFormat, &pfd);
}