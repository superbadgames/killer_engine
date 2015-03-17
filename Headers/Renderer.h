/*--------------------------------------------------------------------
The main Rendering framework for the Engine. A Singleton with a batch
system intregrated into it. It will be called from the Cell class, or
from the main loop at the end of a frame, to make sure that everything
is drawn as it should be.

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
---------------------------------------------------------------------*/
#ifndef RENDERER_H
#define RENDERER_H

//User Defined Includes
#include <Atom.h>
#include <Cell.h>

//3rd party defined Includes
#include <GL/gl.h>
#include <gl/glu.h>

//Predefine class
class Cell;

class Renderer {
	U32		 _maxVerticies;
	Point<>* _verticies;
	Color<>* _colors;
	GLfloat* _uvs;

protected:
	Renderer(void);

public:
	U32		 _batchSize;
	
	~Renderer(void){};

	static Renderer* _instance;
	static Renderer* Instance(void);

	void AddCell(Cell &cell);
	void SetPointers(void);
	void Render(void);
	void ShutDown(void);
};

#endif