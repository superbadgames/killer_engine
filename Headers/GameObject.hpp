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
#include <Atom.h>
#include <Cell.h>
#include <Point.hpp>
#include <Color.hpp>

class GameObject{
private:
	Cell _cell;
	bool _active;

protected:
	

 
public:
	//=====Constructors=====
	GameObject(void) : _cell(), _active(true) {  }
	GameObject(const Cell& cell) : _cell(cell), _active(true) {  }
	GameObject(bool active) : _cell(), _active(active) {  }
	GameObject(const Cell& cell, bool active) : _cell(cell), _active(active) {  }

	//=====Desctructor=====
	//virtual ~GameObject(void){  }

	//virtual void v_ShutDown(void);

	void RenderTriCell(void) { _cell.RenderAsTri(); }
	void RenderSqrCell(void) { _cell.RenderAsSqr(); }
	void RenderHexCell(void) { _cell.RenderAsHex(); }

	//Accessors
	void SetPosition(const point& p) { _cell.SetPosition(p); }
	void SetColor(const color& c)    { _cell.SetColor(c); }
	void SetDimensions(const F32 w, const F32 h)	   { _cell.SetDimensions(w, h); }


	const point& GetPosition(void) { return _cell.GetPosition(); }
	const color& GetColor(void)    { return _cell.GetColor(); }
	const F32    GetWidth(void)    { return _cell.GetWidth(); }
	const bool   GetActive(void)   { return _active; }
	
	//=====Virtual functions=====
	virtual void Update(void)=0;
	virtual void Render(void)=0;

	void SetActive(void)   { _active = true; }
	void SetInactive(void) { _active = false; }
};

#endif