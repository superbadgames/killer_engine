#include <Engine/Map2D.h>

namespace KillerEngine 
{
	Map2D::Map2D(void) : _mapWidth(0),
					   		 _mapHeight(0),
					   		 _mapTopBorder(0),
					   		 _mapBottomBorder(0),
					   		 _mapRightBorder(0),
					   		 _mapLeftBorder(0),
					   		 _bgColor()
	{  }

//=============================================================================
//
//AddObjectToMap
//
//=============================================================================
	void Map2D::AddObjectToMap(GameObject2D* obj)
	{
		_worldObjects.insert(std::map<U32, GameObject2D*>::value_type(obj->GetID(), obj));
		
		if(_worldObjects.find(obj->GetID()) == _worldObjects.end()) 
		{ 
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddMap to _worldObjects"); 
		}
	}

//=============================================================================
//
//RemoveObjectFromMap
//
//=============================================================================
	void Map2D::RemoveObjectFromMap(U32 id)
	{
		std::map<U32, GameObject2D*>::iterator i = _worldObjects.find(id);

		_worldObjects.erase(i);
	}

}//End namespace