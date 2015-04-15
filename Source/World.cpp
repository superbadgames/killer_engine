#include <World.h>
//--------------------------------------------------------------
//InitWorld
//--------------------------------------------------------------
bool World::InitWorld(S32 w, S32 h) {
	_nextID    = 1;
	_mapWidth  = w;
	_mapHeight = h;

	return true;
}

//--------------------------------------------------------------
//AddObjectToWorld
//--------------------------------------------------------------
bool World::AddObjectToWorld(GameObject* obj){
	_worldObjects[_nextID] = obj;
	
	//Add a check to make sure that it was added like it should be	
	_nextID++;
	return true;
}

//--------------------------------------------------------------
//SetBackgroundColor
//--------------------------------------------------------------
void World::SetBackgroundColor() {
	glClearColor(_bgColor.Red, _bgColor.Green, _bgColor.Blue, 0.0f/*alpha*/);
}