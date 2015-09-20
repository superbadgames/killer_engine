
/*========================================================================
The KillerEngine class is designed to be the interface to starting up the
Engine. This class will really just be a function and instance holder for
other classes in the engine, but will actually do very little of its own. 

A lot of the functions that will be here will not be required to use in
order to use the engine. They will be present as helper classes, not
intended for required use. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef KILLER_ENGINE_H
#define KILLER_ENGINE_H
#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Controller.h>
#include <Engine/ProgramWindow.h>
#include <Engine/Renderer.h>
#include <Engine/Timer.h>
#include <Engine/WorldManager.h>
#include <Engine/TextureManager.h>


namespace KillerEngine {

	class KillerEngine {

public:
//==========================================================================================================================
//
//Interface
//
//==========================================================================================================================
		void Init(const S32 width, const S32 height, const text title, const bool fullscreen);

		bool Running(void) { return _worldManager->GetRunning(); }

		void LoadTexture(const text path, const text name, const S32 width, const S32 height) { 
			_textureManager->LoadTexture(path, name, width, height); 
		}
		
		void AddWorldToManager(const text id, World* world) { _worldManager->AddWorld(id, world); }

		void SetActiveWorld(const text id) { _worldManager->SetActiveWorld(id); }

		void Update(void);

		void Render(void);
//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
		static KillerEngine* Instance();		

protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
		KillerEngine(void);

private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================
		static KillerEngine* 	_instance;
			   ErrorManager* 	_errorManager;
			   Controller*   	_controller;
			   ProgramWindow* 	_programWindow;
			   Renderer* 		_renderer;
			   Timer* 			_timer;
			   WorldManager* 	_worldManager;
			   TextureManager* _textureManager;

		

	};

}//End namespace

#endif