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
#include <Engine/Map2D.h>
#include <Engine/GameObject2D.h>
#include <Engine/ErrorManager.h>

//=====STL includes=====
#include <map>

namespace KillerEngine 
{

	class MapManager2D
	{
	private:
		std::map<U32, Map2D*>    _worlds;
		Map2D* 				   _activeMap;
		U32 				   	   _activeMapID;
		bool				   	   _running;			
		static MapManager2D*     _instance;

	public:
		~MapManager2D(void) {  }

		static MapManager2D* Instance();

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void AddMap(Map2D* world);
		
		void RemoveMap(U32 worldID);
		
		void SetActiveMap(U32 worldID);
		
		U32 GetActiveMapID(void) { return _activeMapID; }
		
		void SetRunning(bool r) { _running = r; }
		
		bool GetRunning(void) { return _running; } 

		void AddObjectToMap(U32 id, GameObject2D* obj);

		void RemoveObjectFromMap(U32 worldID, U32 ojbId);

//==========================================================================================================================
//
//Integrators
//
//==========================================================================================================================

		void Update(void);
		
		void Render(void);

	protected:
		MapManager2D(void) : _running(true) {  }

	};

}//End namespace

#endif