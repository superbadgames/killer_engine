#include <Engine/World2D.h>

namespace KillerEngine 
{
	World2D::World2D(void) : mapWidth(0),
					   		 mapHeight(0),
					   		 bgColor()
	{  }

//--------------------------------------------------------------
//AddObjectToWorld
//--------------------------------------------------------------
	void World2D::AddObjectToWorld(GameObject2D* obj)
	{
		_worldObjects.insert(std::map<U32, GameObject2D*>::value_type(obj->GetID(), obj));
		
		if(_worldObjects.find(obj->GetID()) == _worldObjects.end()) 
		{ 
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddWorld to _worldObjects"); 
		}
	}

}//End namespace