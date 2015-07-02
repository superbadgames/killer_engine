/*==========================================================================
The main Rendering framework for the Engine. A Singleton with a batch
system intregrated into it. It will be called from the Cell class, or
from the main loop at the end of a frame, to make sure that everything
is drawn as it should be.

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
==========================================================================*/
#ifndef RENDERER_H
#define RENDERER_H

//==========User defined includes==========
#include <Atom.h>
#include <Cell.h>
#include <ErrorManager.h>

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <wglext.h>
//Predefine class
class Cell;

class Renderer {
private:	
	U32		 _maxVerticies;
	//Point<>* _verticies;
	//Color<>* _colors;
	F32*     _verticies;
	F32*     _colors;
	GLfloat* _uvs;
	GLuint   _renderingProgram;
	GLuint   _vertexArrayObject;

	static const GLchar* _vertexShaderSource[];
	static const GLchar* _tessControlShaderSource[];
	static const GLchar* _tessEvalShaderSource[];
	static const GLchar* _geometryShaderSource[];
	static const GLchar* _fragmentShaderSource[];

	GLuint _CompileShaders(void);
	void   _SetOrthoProjection(void);

protected:
	Renderer(void);

public:
	U32		 _batchSize;
	
	~Renderer(void){  };

	static Renderer* _instance;
	static Renderer* Instance(void);

	void AddCell(Cell &cell);
	void ManualAddData(F32* vertices, U32 numVertices);
	void ManualAddData(F32* vertices, F32* colors, U32 numVertices);
	void SetPointers(void);
	void Render(void);
	void ShutDown(void);
};

#endif