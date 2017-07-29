/*========================================================================
Representation of a 3D model. 

Has:
-Vertices
-Shader(s)

Uses:
Most of these will be stored in a GameObject with values
passed when needed  
-Position
-Orientation
-Scale
-Color
-Texture

Behaviors: 
-Render
-ImportModel

This is not free to use, and cannot be used without the express permission
of Layer8 Games.

Written by Maxwell Miller
========================================================================*/
#ifndef MODEL_H
#define MODEL_H

//=====Engine Includes=====
#include <Engine/Atom.h>

//=====OpenGL Includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

//=====STL Includes=====
#include <vector>

namespace KillerEngine
{
	class Model
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Model(void);

		Model(std::vector<F32> vertices);

		Model(F32* verticeArray, U32 length);

		~Model(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	private:
		static GLuint _shaderProgram;
		std::vector<F32> _vertices;

		
	};//end Class
}//end Namespace
#endif