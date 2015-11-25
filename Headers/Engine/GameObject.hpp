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
	private:
		text 	_id;
		Cell& 	_cell;
		Texture _texture;
		bool 	_active;

	protected:
		

	 
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*

need to re-define this. 

		GameObject(void) : _id(), _cell(), _texture(), _active(false) {  }
		
		GameObject(const text id, const Cell& cell) : _id(id), _cell(cell), _texture(), _active(false) {  }
		
		GameObject(const text id, const Cell& cell, bool active) : _id(id), _cell(cell), _texture(), _active(active) {  }
		
		GameObject(const text id, const Cell& cell, const Texture& texture) : _id(id), _cell(cell), _texture(texture), _active(false) {  }
		
		GameObject(const text id, const Cell& cell, const Texture& texture, bool active) : _id(id), _cell(cell), _texture(texture), _active(active) {  }



		//virtual ~GameObject(void){  }

		//virtual void v_ShutDown(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		const text GetId(void) { return _id; }

		void SetId(text id) { _id = id; }

		const color& GetColor(void) { return _cell.GetColor(); }

		void SetColor(const color& c) { _cell.SetColor(c); }


		const Texture& GetTexture(void) { return _texture; }

		void SetTexture(const Texture& texture) { _texture = texture; }


		const point& GetPosition(void) { return _cell.GetPosition(); }
		
		void SetPosition(const point& p) { _cell.SetPosition(p); }
		
		
		const F32 GetWidth(void) { return _cell.GetWidth(); }

		void SetDimensions(const F32 w, const F32 h) { _cell.SetDimensions(w, h); }
		
		
		const bool   GetActive(void)   { return _active; }

		void SetActive(void)   { _active = true; }
		
		void SetInactive(void) { _active = false; }

//==========================================================================================================================
//
//GameObject Functions
//
//==========================================================================================================================
		void RenderTriCell(void) { _cell.RenderAsTri(); }
		
		void RenderSqrCell(void) { _cell.RenderAsSqr(); }
		
		void RenderHexCell(void) { _cell.RenderAsHex(); }

		void RenderTexturedTriCell(void) { _cell.RenderTexturedTri(_texture); }
		
		void RenderTexturedSqrCell(void) { _cell.RenderTexturedSqr(_texture); }
		
		void RenderTexturedHexCell(void) { _cell.RenderTexturedHex(_texture); }
*/

//==========================================================================================================================
//
//virtual functions
//
//==========================================================================================================================
		virtual void vUpdate(void)=0;
		
		virtual void vRender(void)=0;
	};

}//End namespace

#endif