/*========================================================================
The Game Object is the abstract class that all objects that will be
placed in the game will inherit from. It will hold and define the 
cell, and will include all calls for updating and rendering. There
will be a component map which will hold anything that the object will
need in the game. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

//User defined includes
#include <Atom.h>
#include <Cell.h>
#include <Point.hpp>
#include <Color.hpp>

//3rd party and system includes

class GameObject{
protected:
	Cell _cell;

public:
	GameObject(void){  }
	virtual ~GameObject(void){  }

	//virtual void v_ShutDown(void);

	//Accessors
	void SetPosition(Point<> p) { _cell.SetPosition(p); }
	void SetColor(Color<> c)    { _cell.SetColor(c); }
	void SetScale(F32 s)		{ _cell.SetEvenScale(s); }


	Point<> GetPosition(void) { return _cell.CellPosition(); }
	Color<> GetColor(void)    { return _cell.CellColor(); }
	F32     GetScale(void)    { return _cell.GetEvenScale(); }

	virtual void v_Update(void) {  }
	void         v_Render(void) { _cell.Render(); }

	void SetActive(void)   {  }
	void SetInactive(void) {  }
};

#endif