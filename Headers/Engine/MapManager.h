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
#include <Engine/Map.h>
#include <Engine/GameObject2D.h>
#include <Engine/ErrorManager.h>

//=====STL includes=====
#include <map>

namespace KillerEngine 
{

	class MapManager
	{
	public:
		~MapManager(void) {  }

		static MapManager* Instance();

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void AddMap(Map* world);
		
		void RemoveMap(U32 worldID);
		
		void SetActiveMap(U32 worldID);
		
		U32 GetActiveMapID(void) { return _activeMapID; }
		
		void SetRunning(bool r) { _running = r; }
		
		bool GetRunning(void) { return _running; } 

		void AddObjectToMap(U32 id, GameObject2D* obj);

		void AddObjectToMap(U32 id, GameObject3D* obj);
		
		void Remove2DObjectFromMap(U32 worldID, U32 ojbId);

		void Remove3DObjectFromMap(U32 worldID, U32 ojbId);

//==========================================================================================================================
//
//Integrators
//
//==========================================================================================================================

		void Update(void);
		
		void Render(void);

	protected:
		MapManager(void) : _running(true) {  }

	private:
		std::map<U32, Map*>    _worlds;
		Map* 				   _activeMap;
		U32 				   _activeMapID;
		bool				   _running;			
		static MapManager*     _instance;

	};

}//End namespace

#endif