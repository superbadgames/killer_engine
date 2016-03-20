/*========================================================================
The Game Object is the abstract class, (PURE VIRTUAL) that all objects that 
will be placed in the game will inherit from. It will hold and define the 
cell, and will include all calls for updating and rendering. Therewill be a 
component map which will hold anything that the object will need in the game. 

All of the functions in this class are inlined becuase they are all 
trivial. The virtual functions are there so that the interface can
be the same for all derived classes. By doing this, the world manager
will be able to have a map of GameObjects to be rendered in a specific
world. 

The GameObject itself is an interface to generic functions that each obj-
ect that will be rendered will need to be drawn to the screen. The GameObj-
ect holds a private Sprite member that will contain all the logic for which
rendering algorithm is used. 

Accessors are created for the derived classes to access the cell, but the 
cell is to be accessed directly only by the GameObject itself. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

//=====Engine Includes======
#include <Engine/Atom.h>
#include <Engine/Sprite.h>
#include <Engine/Texture.hpp>

namespace KillerEngine 
{
	
	class GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		//GameObject(void);


		//~GameObject(void);

		//void v_ShutDown(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		virtual void v_Update(void)=0;
		
		virtual void v_Render(void)=0; 

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//=====ID=====		
		const string GetID(void) { return __id; }

		void SetID(string id) { __id = id; }

//=====Position=====
		const Vec2& GetPosition(void) { return __position; }
		
		void SetPosition(Vec2& pos) { __position = pos; }

		void SetPosition(F32 x, F32 y) { __position = Vec2(x, y); }

//=====Dimensions=====
//Settings are virtual so that each GameObject
//Can make sure to update its sprite, if it has one
//with a default version in the case of no sprite.
		
		const F32 GetWidth(void) { return __width; }

		virtual void SetWidth(F32 w) { __width = w; }

		const F32 GetHeight(void) { return __height; }

		virtual void SetHeight(F32 h) { __height = h; }

		virtual void SetDimensions(const F32 w, const F32 h) 
		{
			__width = w;
			__height = h;
		}

//=====Color=====
		const Col* GetColor(void) { return &__color; }

		void SetColor(Col& col) { __color = col; }

//=====Texture=====
		const Texture* GetTexture(void) { return &__texture; }

		void SetTexture(Texture& texture) { __texture = texture; }

//=====Active=====
		const bool GetActive(void)   { return __active; }

		void SetActive(void)   { __active = true; }
		
		void SetInactive(void) { __active = false; }



	protected:
		string 	 __id;
		Vec2     __position;
		F32      __width;
		F32      __height;
		Col      __color;
		Texture  __texture;
		bool 	 __active;
	};

}//End namespace

#endif