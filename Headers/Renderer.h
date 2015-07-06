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

//=====STD Includes=====
#include <vector>

//Predefine class
class Cell;

class Renderer {
private:
	static Renderer* _instance;
	
	U32 _maxBatchSize;
	U32 _totalVerticesInBatch;

	std::vector<F32> _triVerticies;
	std::vector<F32> _triColors;
	std::vector<F32> _sqrVertices;
	std::vector<F32> _sqrColors;
	std::vector<F32> _hexVertices;
	std::vector<F32> _hexColors;	
	
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
	~Renderer(void){ };
	static Renderer* Instance(void);

	void AddTri(const Cell& cell);
	void AddSqr(const Cell& cell);
	void AddHex(const Cell& cell);
	void Draw(void);
	//void ShutDown(void);
};

#endif