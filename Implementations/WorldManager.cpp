#include <Engine/WorldManager.h>

namespace KillerEngine {

//--------------------------------------------------------------
//Instance
//--------------------------------------------------------------
WorldManager* WorldManager::_instance = NULL;

WorldManager* WorldManager::Instance(void) {
	if(_instance == NULL) { _instance = new WorldManager; }
	return _instance;
}

//--------------------------------------------------------------
//AddWorld
//--------------------------------------------------------------
void WorldManager::AddWorld(const text worldID, World* world) {
	_worlds[worldID] = world; 
}

//--------------------------------------------------------------
//RemoveWorld
//--------------------------------------------------------------
void WorldManager::RemoveWorld(text worldID) {
	auto w = _worlds.find(worldID);
	_worlds.erase(w);
}

//--------------------------------------------------------------
//SetActiveWorld
//--------------------------------------------------------------
void WorldManager::SetActiveWorld(text worldID) {
	_activeWorldID = worldID;
	auto w = _worlds.find(worldID);
	_activeWorld = w->second;
	_activeWorld->ActivateBackgroundColor();
}

//--------------------------------------------------------------
//Update
//--------------------------------------------------------------
void WorldManager::Update(void) {
	_activeWorld->Update();
}

//--------------------------------------------------------------
//Render
//--------------------------------------------------------------
void WorldManager::Render(void) {
	_activeWorld->Render();
}

}//End namsepace