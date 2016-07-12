#include <Engine/World2D.h>

namespace KillerEngine 
{
//--------------------------------------------------------------
//Static Members
//--------------------------------------------------------------
	U32 World2D::_nextID = 1;

	World2D::World2D(void) : mapWidth(0),
					   		 mapHeight(0),
					   		 bgColor(),
					   		 _ID(_nextID)
	{
		++_nextID;
	}

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