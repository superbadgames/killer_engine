#include <Engine/KillerEngine2D.h>

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
	void KillerEngine2D::Init(const S32 width, const S32 height, const string title, const bool fullscreen) 
	{
		_errorManager = ErrorManager::Instance();
		_timer = KM::Timer::Instance();
		_worldManager = WorldManager2D::Instance();
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
	void KillerEngine2D::Update(void) 
	{
		_programWindow->ProcessWndEvents();

		_timer->Update();
		
		_controller->UpdateKeyboard();
		
		_worldManager->Update();
	}

//=======================================================================================================
//FunctionName
//=======================================================================================================
	void KillerEngine2D::Render(void) 
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
	KillerEngine2D* KillerEngine2D::_instance = NULL;

	KillerEngine2D* KillerEngine2D::Instance(void) 
	{
		if(_instance == NULL) { _instance = new KillerEngine2D(); }

		return _instance;
	}

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
		KillerEngine2D::KillerEngine2D(void) {  }


}//End namespace