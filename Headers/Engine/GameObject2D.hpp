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
	
	class GameObject2D
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
		const U32 GetID(void) { return ID; }

		void SetID(void) 
		{
			ID = _nextID;
			++_nextID;
		}

//=====Dimensions=====
//Settings are virtual so that each GameObject
//Can make sure to update its sprite, if it has one
//with a default version in the case of no sprite.
		
		const F32 GetWidth(void) { return width; }

		virtual void SetWidth(F32 w) { width = w; }

		const F32 GetHeight(void) { return height; }

		virtual void SetHeight(F32 h) { height = h; }

		virtual void SetDimensions(const F32 w, const F32 h) 
		{
			width = w;
			height = h;
		}

//=====Color=====
		const Col* GetColor(void) { return &color; }

		void SetColor(Col& col) { color = col; }

//=====Texture=====
		const Texture* GetTexture(void) { return &texture; }

		void SetTexture(Texture& texture) { texture = texture; }

//=====Active=====
		const bool GetActive(void)   { return active; }

		void SetActive(void)   { active = true; }
		
		void SetInactive(void) { active = false; }

//=====Position=====
		const Vec2& GetPosition(void) { return position; }
		
		void SetPosition(Vec2& pos) { position = pos; }

		void SetPosition(F32 x, F32 y) { position = Vec2(x, y); }

//=====Velocity=====
		const Vec2& GetVelocity(void) { return velocity; }

		void SetVelocity(Vec2& v) { velocity = v; }

		void SetVelocity(F32 x, F32 y) { velocity = Vec2(x, y); }

//=====Acceleration=====
		const Vec2& GetAcceleration(void) { return acceleration; }

		void SetAcceleration(Vec2& a) { acceleration = a; }

		void SetAcceleration(F32 x, F32 y) { acceleration = Vec2(x, y); }



	protected:	
		U32 	 ID;
		bool 	 active;
		F32      width;
		F32      height;
		Col      color;
		Texture  texture;
		
		Vec2     position;
		Vec2	 velocity;
		Vec2	 acceleration;

	private:
		static U32 _nextID;
	};

	U32 GameObject2D::_nextID = 1;

}//End namespace

#endif