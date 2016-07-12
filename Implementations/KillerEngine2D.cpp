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
		ProgramWindow::Instance()->Init(width, height, title, fullscreen);

		Controller::Instance()->Init(ProgramWindow::Instance()->GetHINSTANCE(), ProgramWindow::Instance()->GetHWND());

		ErrorManager::Instance()->DisplayErrors();
	}

//=======================================================================================================
//Update
//=======================================================================================================
	void KillerEngine2D::Update(void) 
	{
		ProgramWindow::Instance()->ProcessWndEvents();

		KM::Timer::Instance()->Update();
		
		Controller::Instance()->UpdateKeyboard();
		
		WorldManager2D::Instance()->Update();
	}

//=======================================================================================================
//FunctionName
//=======================================================================================================
	void KillerEngine2D::Render(void) 
	{
		WorldManager2D::Instance()->Render();

		Renderer::Instance()->Draw();

		ProgramWindow::Instance()->BufferSwap();
		
		ErrorManager::Instance()->DisplayErrors();
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