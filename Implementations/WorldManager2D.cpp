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
	void WorldManager2D::AddWorld(const string worldID, World2D* world) 
	{
		_worlds[worldID] = world; 
	}

//--------------------------------------------------------------
//RemoveWorld
//--------------------------------------------------------------
	void WorldManager2D::RemoveWorld(string worldID) 
	{
		auto w = _worlds.find(worldID);
		_worlds.erase(w);
	}

//--------------------------------------------------------------
//SetActiveWorld
//--------------------------------------------------------------
	void WorldManager2D::SetActiveWorld(string worldID) 
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

}//End namsepace