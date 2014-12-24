#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

//User defined includes
#include <Example.h>
#include <GLWindow.h>

//3rd party includes
#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     cmdLine,
                   int       cmdShow)
{
    //------------------------------------------------------Initialization of Window
    //Set up window settings
    const int windowWidth      = 1024;
    const int windowHeight     = 768;
    const int windowBPP        = 32;
    const int windowFullScreen = false;

    //OpenGL window we will control
    GLWindow programWindow(hInstance);

    //Example program code
    Example example;

    //Attach example to window
    programWindow.AttachExample(&example);

    if(!programWindow.Create(windowWidth, windowHeight, windowBPP, windowFullScreen)) {
      MessageBox(NULL, "Unable to create the OpenGL Window", "An Error occured", MB_ICONERROR | MB_OK);
      programWindow.Destroy();
      return 1;
    }

    if(!example.init()) {
      MessageBox(NULL, "Could not initialize the application", "An Error occured", MB_ICONERROR | MB_OK);
      programWindow.Destroy();
      return 1;
    }

    //-------------------------------------------------------Main loop of program
    while(programWindow.isRunning()) {
      programWindow.ProcessEvents();

	  float elapsedTime = programWindow.GetElapsedSeconds();

      example.Prepare(elapsedTime);
      example.Render();

      programWindow.MySwapBuffers();
    }

    example.ShutDown();
    programWindow.Destroy();
    return 0;
}