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

//3rd party defined Includes
#include <GL/gl.h>
#include <gl/glu.h>


class Renderer {
private:
	U32  _maxVerticies;
	F32* _verticies;
	F32* _colors;
	F32* _uvs;
	U32  _batchSize;

	static Renderer* _instance;

protected:
	Renderer(void);

public:
	~Renderer(void){};

	static Renderer* Instance(void);

	void AddCell(void);//void for now, will take a cell after that class has been added. Implement later
	void SetPointers(void);
	void Render(void);
	void ShutDown(void);
};

#endif