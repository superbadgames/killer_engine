#include <Engine/KillerEngine.h>

namespace KillerEngine 
{
//==========================================================================================================================
//
//Interface
//
//==========================================================================================================================
//=======================================================================================================
//Init
//=======================================================================================================
	void KillerEngine::Init(const S32 width, const S32 height, const text title, const bool fullscreen) 
	{
		_errorManager = ErrorManager::Instance();
		_timer = Timer::Instance();
		_worldManager = WorldManager::Instance();
		_controller = Controller::Instance();
		_programWindow = ProgramWindow::Instance();

		_programWindow->Init(width, height, title, fullscreen);

		_textureManager = TextureManager::Instance();
		_renderer = Renderer::Instance();

		_controller->Init(_programWindow->GetHINSTANCE(), _programWindow->GetHWND());

		_errorManager->DisplayErrors();
	}

//=======================================================================================================
//Update
//=======================================================================================================
	void KillerEngine::Update(void) 
	{
		_programWindow->ProcessWndEvents();

		_timer->Update();
		
		_controller->UpdateKeyboard();
		
		_worldManager->Update();
	}

//=======================================================================================================
//FunctionName
//=======================================================================================================
	void KillerEngine::Render(void) 
	{
		_worldManager->Render();

		_renderer->Draw();

		_programWindow->BufferSwap();
		
		_errorManager->DisplayErrors();
	}

//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
	KillerEngine* KillerEngine::_instance = NULL;

	KillerEngine* KillerEngine::Instance(void) 
	{
		if(_instance == NULL) { _instance = new KillerEngine(); }

		return _instance;
	}

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
		KillerEngine::KillerEngine(void) {  }


}//End namespace