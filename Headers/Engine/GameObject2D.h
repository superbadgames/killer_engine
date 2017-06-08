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
#include <Engine/ErrorManager.h>

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
		GameObject2D(void);


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
		const U32 GetID(void) 
		{ 
			return _ID; 
		}

		void SetID(void) 
		{
			_ID = _nextID;
			++_nextID;

			//This is here to make sure that by this point the user has 
			//added a sprite to the game object.
			if(_sprite == NULL)
			{
				ErrorManager::Instance()->SetError(EC_GameObject, "Error! Sprite is Null, you must pass a pointer to the sprite you wish to use before you call GameObject::SetID().");
			}
		}

//=====Dimensions=====
//Settings are virtual so that each GameObject
//Can make sure to update its sprite, if it has one
//with a default version in the case of no sprite.
		
		const F32 GetWidth(void) 
		{ 
			return _sprite->GetWidth(); 
		}

		virtual void SetWidth(F32 w) 
		{ 
			_sprite->SetWidth(w); 
		}

		const F32 GetHeight(void) 
		{ 
			return _sprite->GetHeight(); 
		}

		virtual void SetHeight(F32 h) 
		{ 
			_sprite->SetHeight(h); 
		}

		virtual void SetDimensions(const F32 w, const F32 h) 
		{ 
			_sprite->SetDimensions(w, h); 
		}

//=====Color=====
		const Col& GetColor(void) 
		{ 
			return _sprite->GetColor();	 
		}

		void SetColor(Col& col) 
		{ 
			_sprite->SetColor(col); 
		}

		void SetColor(F32 red, F32 blue, F32 green) 
		{ 
			_sprite->SetColor(Col(red, blue, green)); 
		}

//=====Texture=====
		const  U32 GetTextureID(void) 
		{ 
			return _sprite->GetTextureID(); 
		}

		void SetTexture(U32 tID, const F32 top, const F32 bottom, const F32 right, const F32 left) 
		{ 
			_sprite->SetTexture(tID, top, bottom, right, left);
		}

		void SetTexture(U32 tID)
		{
			_sprite->SetTexture(tID, 0.0f, 1.0f, 0.0f, 1.0f);

		}

//=====Active=====
		const bool GetActive(void) 
		{ 
			return _active; 
		}

		void SetActive(void)   
		{ 
			_active = true; 
		}
		
		void SetInactive(void) 
		{ 
			_active = false; 
		}

//=====Sprite=====
		const Sprite* GetSprite(void) 
		{ 
			return _sprite; 
		}

		void SetSprite(Sprite* s) 
		{ 
			_sprite = s; 
		}	

		void RenderSprite(void) 
		{ 
			_sprite->v_RenderSprite();  
		}	

//=====Position=====
		const Vec2& GetPosition(void) 
		{ 
			return _position; 
		}
		
		void SetPosition(Vec2& pos) 
		{ 
			_position = pos;
			_sprite->SetPosition(_position); 
		}

		void SetPosition(F32 x, F32 y) 
		{ 
			_position = Vec2(x, y);
			_sprite->SetPosition(_position);
		}

		void SetScaledPosition(const Vec2& v, F32 scale)
		{
			_position.AddScaledVector(v, scale);
			_sprite->SetPosition(_position);
		}

		void SetPositionNoSprite(Vec2& pos)
		{
			_position = pos;
		}

		void virtual v_SetPosition(Vec2& pos)
		{
			SetPosition(pos);
		}

		void virtual v_SetPosition(F32 x, F32 y)
		{
			SetPosition(x, y);
		}

//=====Velocity=====
		const Vec2& GetVelocity(void) 
		{ 
			return _velocity; 
		}

		void SetVelocity(Vec2& v) 
		{ 
			_velocity = v; 
		}

		void SetScaledVelocity(const Vec2& vec, F32 scale)
		{
			_velocity.AddScaledVector(vec, scale);
		}

		void SetVelocity(F32 x, F32 y) 
		{ 
			_velocity = Vec2(x, y); 
		}

//=====Acceleration=====
		const Vec2& GetAcceleration(void) 
		{ 
			return _acceleration; 
		}

		void SetAcceleration(Vec2& a) 
		{ 
			_acceleration = a; 
		}

		void SetScaledAccelleration(const Vec2& vec, F32 scale)
		{
			_acceleration.AddScaledVector(vec, scale);
		}

		void SetAcceleration(F32 x, F32 y) 
		{
		 	_acceleration = Vec2(x, y); 
		}

	protected:
//==========================================================================================================================
//
//GameObject Functions
//
//==========================================================================================================================
//=====Sprite Factories=====
//==SqrSprite==
		void CreateSqrSprite(Vec2& pos, Col& col, Texture& texture);
		
		void CreateSqrSprite(void);


	private:	
		static U32 	_nextID;
		U32 		_ID;
		bool 	 	_active;
		Sprite*  	_sprite;
		Vec2     	_position;
		Vec2	 	_velocity;
		Vec2	 	_acceleration;	
	};

	

}//End namespace

#endif