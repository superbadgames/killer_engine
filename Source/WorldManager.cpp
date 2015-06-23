#include <WorldManager.h>

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
bool WorldManager::AddWorld(text worldID, World* world) {
	_worlds[worldID] = world;
	return true;
}

//--------------------------------------------------------------
//RemoveWorld
//--------------------------------------------------------------
bool WorldManager::RemoveWorld(text worldID) {
	auto w = _worlds.find(worldID);
	_worlds.erase(w);
	return true;
}

//--------------------------------------------------------------
//SetActiveWorld
//--------------------------------------------------------------
bool WorldManager::SetActiveWorld(text worldID) {
	_activeWorldID = worldID;
	auto w = _worlds.find(worldID);
	_activeWorld = w->second;
	_activeWorld->SetBackgroundColor();
	return true;
}

//--------------------------------------------------------------
//Update
//--------------------------------------------------------------
void WorldManager::Update(void) {
	_activeWorld->v_Update();
}

//--------------------------------------------------------------
//Render
//--------------------------------------------------------------
void WorldManager::Render(void) {
	_activeWorld->v_Render();
}