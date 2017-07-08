#include <Engine/MapManager.h>

namespace KillerEngine 
{

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//==========================================================================================================================
//Singleton
//==========================================================================================================================
	MapManager* MapManager::_instance = NULL;

	MapManager* MapManager::Instance(void) 
	{
		if(_instance == NULL) { _instance = new MapManager; }
		return _instance;
	}

//==========================================================================================================================
//
//Map Accessors
//
//==========================================================================================================================
	void MapManager::AddMap(Map* world) 
	{
		_worlds.insert(std::map<U32, Map*>::value_type(world->GetID(), world));
		
		if(_worlds.find(world->GetID()) == _worlds.end()) 
		{ 
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddMap to MapManager"); 
		}
	}

	void MapManager::RemoveMap(U32 worldID) 
	{
		auto w = _worlds.find(worldID);
		_worlds.erase(w);
	}

//==========================================================================================================================
//
//SetActiveMap
//
//==========================================================================================================================
	void MapManager::SetActiveMap(U32 worldID) 
	{
		_activeMapID = worldID;
		auto w = _worlds.find(worldID);
		_activeMap = w->second;
		_activeMap->ActivateBackgroundColor();
	}

//==========================================================================================================================
//
//Update
//
//==========================================================================================================================
	void MapManager::Update(void) 
	{
		_activeMap->v_Update();
	}

//==========================================================================================================================
//
//Render
//
//==========================================================================================================================
	void MapManager::Render(void) 
	{
		_activeMap->v_Render();
	}

//==========================================================================================================================
//
//Add/Remove Objects from Map
//
//This function will add a GameObject to an existing, registered world. It will check to make sure that the called worled
//in fact is registered with the manager, and will throw and error if it is not. 
//	
//==========================================================================================================================
	void MapManager::AddObjectToMap(U32 id, GameObject2D* obj)
	{
		if(_worlds.find(id) != _worlds.end()) { _worlds[id]->AddObjectToMap(obj); } 
		else ErrorManager::Instance()->SetError(EC_KillerEngine, "MapManager -> Tried to call the AddObjectToMap() function for a world that does not exist.");
	}

	void MapManager::AddObjectToMap(U32 id, GameObject3D* obj)
	{
		if(_worlds.find(id) != _worlds.end()) { _worlds[id]->AddObjectToMap(obj); } 
		else ErrorManager::Instance()->SetError(EC_KillerEngine, "MapManager -> Tried to call the AddObjectToMap() function for a world that does not exist.");
	}

	void MapManager::Remove2DObjectFromMap(U32 worldID, U32 objID)
	{
		if(_worlds.find(worldID) != _worlds.end()) { _worlds[worldID]->Remove2DObjectFromMap(objID); }
	}

	void MapManager::Remove3DObjectFromMap(U32 worldID, U32 objID)
	{
		if(_worlds.find(worldID) != _worlds.end()) { _worlds[worldID]->Remove3DObjectFromMap(objID); }
	}

}//End namsepace