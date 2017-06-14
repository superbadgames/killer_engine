#include <Engine/GameObject3D.h>

namespace KillerEngine
{
	U32 GameObject3D::_nextID = 1; 

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	GameObject3D::GameObject3D(void) : _active(true), _position(Vec3(0.0f)), _velocity(Vec3(0.0f)), _acceleration(0)
	{
		SetID();
	}

	GameObject3D::~GameObject3D(void)
	{  }
}//end namespace