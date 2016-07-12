
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
#include <Engine/WorldManager2D.h>
#include <Engine/TextureManager.h>

//======Math includes=====
//#include <Engine/RandomGen.h>

namespace KM = KillerMath;

namespace KillerEngine 
{

	class KillerEngine2D 
	{

	public:
//==========================================================================================================================
//
//Interface
//
//==========================================================================================================================
		void Init(const S32 width, const S32 height, const string title, const bool fullscreen);

		bool Running(void) { return WorldManager2D::Instance()->GetRunning(); }

		void LoadTexture(const string path, const string name, const S32 width, const S32 height) 
		{ 
			TextureManager::Instance()->LoadTexture(path, name, width, height); 
		}
		
		void AddWorldToManager(World2D* world) { WorldManager2D::Instance()->AddWorld(world); }

		void SetActiveWorld(const U32 id) { WorldManager2D::Instance()->SetActiveWorld(id); }

		void Update(void);

		void Render(void);
//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
		static KillerEngine2D* Instance();		

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
		KillerEngine2D(void);

	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================
		static KillerEngine2D* 	_instance;

	};

}//End namespace

#endif