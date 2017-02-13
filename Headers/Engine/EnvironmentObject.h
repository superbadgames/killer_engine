/*========================================================================
This is an implementation of a GameObject which will reprents static, 
unmoving background objects which the player will not be allowed to pass
through. These are things like rocks, trees, houses, etc. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/SqrSprite.h>

namespace KillerEngine
{
	class EnvironmentObject : public GameObject2D
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		EnvironmentObject(void);

		EnvironmentObject(Vec2& pos, F32 w, F32 h);

		EnvironmentObject(Vec2& pos, U32 textureID, F32 w, F32 h);

		~EnvironmentObject(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Update(void) {  }

		void v_Render(void) { GameObject2D::RenderSprite(); }

	private:
		
	};//end Class
}//end Namespace
#endif