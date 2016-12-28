#include <Engine/WorldManager2D.h>

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
	WorldManager2D* WorldManager2D::_instance = NULL;

	WorldManager2D* WorldManager2D::Instance(void) 
	{
		if(_instance == NULL) { _instance = new WorldManager2D; }
		return _instance;
	}

//--------------------------------------------------------------
//AddWorld
//--------------------------------------------------------------
	void WorldManager2D::AddWorld(World2D* world) 
	{
		_worlds.insert(std::map<U32, World2D*>::value_type(world->GetID(), world));
		
		if(_worlds.find(world->GetID()) == _worlds.end()) 
		{ 
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddWorld to WorldManager"); 
		}
	}

//--------------------------------------------------------------
//RemoveWorld
//--------------------------------------------------------------
	void WorldManager2D::RemoveWorld(U32 worldID) 
	{
		auto w = _worlds.find(worldID);
		_worlds.erase(w);
	}

//--------------------------------------------------------------
//SetActiveWorld
//--------------------------------------------------------------
	void WorldManager2D::SetActiveWorld(U32 worldID) 
	{
		_activeWorldID = worldID;
		auto w = _worlds.find(worldID);
		_activeWorld = w->second;
		_activeWorld->ActivateBackgroundColor();
	}

//--------------------------------------------------------------
//Update
//--------------------------------------------------------------
	void WorldManager2D::Update(void) 
	{
		_activeWorld->Update();
	}

//--------------------------------------------------------------
//Render
//--------------------------------------------------------------
	void WorldManager2D::Render(void) 
	{
		_activeWorld->Render();
	}

//==========================================================================================================================
//
//AddObjectToWorld
//
//This function will add a GameObject to an existing, registered world. It will check to make sure that the called worled
//in fact is registered with the manager, and will throw and error if it is not. 
//	
//==========================================================================================================================
	void WorldManager2D::AddObjectToWorld(U32 id, GameObject2D* obj)
	{
		if(_worlds.find(id) != _worlds.end()) { _worlds[id]->AddObjectToWorld(obj); } 
		else ErrorManager::Instance()->SetError(EC_KillerEngine, "WorldManager2D -> Tried to call the AddObjectToWorld() function for a world that does not exist.");
	}

//==========================================================================================================================
//
//RemoveObjectFromWorld
//	
//==========================================================================================================================

	void WorldManager2D::RemoveObjectFromWorld(U32 worldID, U32 objID)
	{
		if(_worlds.find(worldID) != _worlds.end()) { _worlds[worldID]->RemoveObjectFromWorld(objID); }
	}

}//End namsepace