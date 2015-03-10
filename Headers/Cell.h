/*--------------------------------------------------------------------
The Cell, or rendering cell is the basic Geometric perimitive that any
game object or entity that is to be rendered will have. It will be the 
OGL verticies that make up the position on the screen. While it will
never be called on its own, it will be part of the rendered game objects.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
----------------------------------------------------------------------*/

#ifndef CELL_H
#define CELL_H

//Killer1 inlucdes
#include <Atom.h>

//3rd party and system includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>


class Cell {
public:
	Cell(void);

	bool Init(void);
	void ShutDown(void);
	void Prepare(void);
	void Render(void);

private:
	
};

#endif