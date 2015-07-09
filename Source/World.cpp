#include <World.h>

World::World(void): _errorManager(ErrorManager::Instance()),
					_nextID(1),
					_mapWidth(0),
					_mapHeight(0) {  }

//--------------------------------------------------------------
//InitWorld
//--------------------------------------------------------------
/*void World::InitWorld(S32 w, S32 h) { 
	 _mapWidth  = w;
	 _mapHeight = h; 
 }*/

//--------------------------------------------------------------
//AddObjectToWorld
//--------------------------------------------------------------
void World::AddObjectToWorld(GameObject* obj){
	_worldObjects[_nextID] = obj;
	
	//Add a check to make sure that it was added like it should be
	if(_worldObjects.find(_nextID) == _worldObjects.end()) { _errorManager->SetError(EC_KillerEngine, "Unable to AddWorld to _worldObjects"); }

	_nextID++;
}

//--------------------------------------------------------------
//SetBackgroundColor
//--------------------------------------------------------------
void World::SetBackgroundColor() {
	glClearColor(_bgColor.GetRed(), _bgColor.GetGreen(), _bgColor.GetBlue(), _bgColor.GetAlpha());
}