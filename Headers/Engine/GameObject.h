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
ect holds a private Cell member that will contain all the logic for which
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
#include <Engine/Cell.h>
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
//Accessors
//
//==========================================================================================================================
//=====ID=====		
		const text GetId(void) { return __id; }

		void SetId(text id) { __id = id; }

//=====Position=====
		const point& GetPosition(void) { return __position; }
		
		void SetPosition(const point& pos) { __position = pos; }

		void SetPosition(F32 x, F32 y) { __position = point(x, y); }

//=====Dimensions=====
		const F32 GetWidth(void) { return __width; }

		void SetWidth(F32 w) { __width = w; }

		const F32 GetHeight(void) { return __height; }

		void SetHeight(F32 h) { __height = h; }

		void SetDimensions(const F32 w, const F32 h) 
		{
			__width = w;
			__height = h;
		}

//=====Color=====
		const color& GetColor(void) { return __color; }

		void SetColor(const color& col) { __color = col; }

//=====Texture=====
		const Texture& GetTexture(void) { return __texture; }

		void SetTexture(const Texture& texture) { __texture = texture; }

//=====Active=====
		const bool GetActive(void)   { return __active; }

		void SetActive(void)   { __active = true; }
		
		void SetInactive(void) { __active = false; }

//==========================================================================================================================
//
//GameObject Functions
//
//==========================================================================================================================
		virtual void v_Update(void)=0;
		
		virtual void v_Render(void)=0; 

	protected:
		text 	__id;
		point   __position;
		F32     __width;
		F32     __height;
		color   __color;
		Texture __texture;
		bool 	__active;
	};

}//End namespace

#endif