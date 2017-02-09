#include <Engine/MapManager2D.h>

namespace KillerEngine 
{

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//--------------------------------------------------------------
//Instance
//--------------------------------------------------------------
	MapManager2D* MapManager2D::_instance = NULL;

	MapManager2D* MapManager2D::Instance(void) 
	{
		if(_instance == NULL) { _instance = new MapManager2D; }
		return _instance;
	}

//--------------------------------------------------------------
//AddMap
//--------------------------------------------------------------
	void MapManager2D::AddMap(Map2D* world) 
	{
		_worlds.insert(std::map<U32, Map2D*>::value_type(world->GetID(), world));
		
		if(_worlds.find(world->GetID()) == _worlds.end()) 
		{ 
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddMap to MapManager"); 
		}
	}

//--------------------------------------------------------------
//RemoveMap
//--------------------------------------------------------------
	void MapManager2D::RemoveMap(U32 worldID) 
	{
		auto w = _worlds.find(worldID);
		_worlds.erase(w);
	}

//--------------------------------------------------------------
//SetActiveMap
//--------------------------------------------------------------
	void MapManager2D::SetActiveMap(U32 worldID) 
	{
		_activeMapID = worldID;
		auto w = _worlds.find(worldID);
		_activeMap = w->second;
		_activeMap->ActivateBackgroundColor();
	}

//--------------------------------------------------------------
//Update
//--------------------------------------------------------------
	void MapManager2D::Update(void) 
	{
		_activeMap->Update();
	}

//--------------------------------------------------------------
//Render
//--------------------------------------------------------------
	void MapManager2D::Render(void) 
	{
		_activeMap->Render();
	}

//==========================================================================================================================
//
//AddObjectToMap
//
//This function will add a GameObject to an existing, registered world. It will check to make sure that the called worled
//in fact is registered with the manager, and will throw and error if it is not. 
//	
//==========================================================================================================================
	void MapManager2D::AddObjectToMap(U32 id, GameObject2D* obj)
	{
		if(_worlds.find(id) != _worlds.end()) { _worlds[id]->AddObjectToMap(obj); } 
		else ErrorManager::Instance()->SetError(EC_KillerEngine, "MapManager2D -> Tried to call the AddObjectToMap() function for a world that does not exist.");
	}

//==========================================================================================================================
//
//RemoveObjectFromMap
//	
//==========================================================================================================================

	void MapManager2D::RemoveObjectFromMap(U32 worldID, U32 objID)
	{
		if(_worlds.find(worldID) != _worlds.end()) { _worlds[worldID]->RemoveObjectFromMap(objID); }
	}

}//End namsepace