#include <Engine/GameObject2D.h>

namespace KillerEngine 
{
	U32 GameObject2D::_nextID = 1;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	GameObject2D::GameObject2D(void) : _ID(0), _active(true), _sprite(NULL), _position(0), _velocity(0), _acceleration(0)
	{  }

}