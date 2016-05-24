#include <Engine/World2D.h>

namespace KillerEngine 
{

//--------------------------------------------------------------
//AddObjectToWorld
//--------------------------------------------------------------
	void World2D::AddObjectToWorld(string objId, GameObject2D* obj)
	{
		_worldObjects[objId] = obj;
		
		if(_worldObjects.find(objId) == _worldObjects.end()) { _errorManager->SetError(EC_KillerEngine, "Unable to AddWorld to _worldObjects"); }
	}

}//End namespace