/*========================================================================
The holder and controller of the the world objects. This will act as 
both a singleton and a state maching controller, where each world will
be a state that can be set to active. 

For now, all of the states that are to be used will be instantiated 
during the initialization in the main loop, however later, each level
will only be created once it is called, as part of a loading screen.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/

#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/World2D.h>
#include <Engine/ErrorManager.h>

//=====STL includes=====
#include <map>

namespace KillerEngine 
{

	class WorldManager2D
	{
	private:
		std::map<U32, World2D*>    _worlds;
		World2D* 				   _activeWorld;
		U32 				   	   _activeWorldID;
		bool				   	   _running;			
		static WorldManager2D*     _instance;

	public:
		~WorldManager2D(void) {  }

		static WorldManager2D* Instance();

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void AddWorld(World2D* world);
		
		void RemoveWorld(U32 worldID);
		
		void SetActiveWorld(U32 worldID);
		
		U32 GetActiveWorldID(void) { return _activeWorldID; }
		
		void SetRunning(bool r) { _running = r; }
		
		bool GetRunning(void) { return _running; } 

//==========================================================================================================================
//
//Integrators
//
//==========================================================================================================================

		void Update(void);
		
		void Render(void);

	protected:
		WorldManager2D(void) : _running(true) {  }

	};

}//End namespace

#endif