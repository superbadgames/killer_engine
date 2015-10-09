/*==========================================================================
The main Rendering framework for the Engine. A Singleton with a batch
system intregrated into it. It will be called from the Cell class, or
from the main loop at the end of a frame, to make sure that everything
is drawn as it should be.

Add*

There is an Add function for Triangles, Squares and Hexagons. These are:
AddTri()
AddSqr()
AddHex()

These take the position of a cell, then create F32 points, storing them in an std::vector, which is 
passed to OGL during the Draw().  

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
==========================================================================*/
#ifndef RENDERER_H
#define RENDERER_H

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Cell.h>
#include <Engine/ProgramWindow.h>
#include <Engine/TextureManager.h>
#include <Engine/Texture.hpp>
#include <Engine/ErrorManager.h>

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

//=====SOIL includes=====
#include <SOIL/SOIL.h>


//=====STL Includes=====
#include <vector>

namespace KillerEngine 
{

	//=====Foreward delcaration=====
	class Cell;

	class Renderer 
	{
	private:
		static Renderer* 	 _instance;
		ErrorManager* 		 _errorManager;
		ProgramWindow* 		 _programWindow;
		TextureManager* 	 _textureManager;
		U32 				 _maxBatchSize;
		U32 				 _totalVerticesInBatch;
		U32 				 _triBatch;
		U32 				 _sqrBatch;
		U32 				 _hexBatch;
		std::vector<F32> 	 _triVerticies;
		std::vector<F32> 	 _triColors;
		std::vector<F32>     _triUVs;
		std::vector<F32> 	 _sqrVertices;
		std::vector<F32> 	 _sqrColors;
		std::vector<F32> 	 _sqrUVs;
		std::vector<F32> 	 _hexVertices;
		std::vector<F32> 	 _hexColors;
		std::vector<F32>	 _hexUvs;	
		GLuint				 _renderingProgramColored;
		GLuint   			 _renderingProgramTextured;
		GLuint   			 _vertexArrayObject;
		static const GLchar* _vertexShaderSourceColor[];
		static const GLchar* _vertexShaderSourceTexture[];
		static const GLchar* _fragmentShaderSourceColor[];
		static const GLchar* _fragmentShaderSourceTexture[];

//==========================================================================================================================
//
//Private Renderer Functions
//
//==========================================================================================================================
		void _CompileShaders(void);
		
		void   _SetOrthoProjection(void);

	public:
//==========================================================================================================================
//
//Destructor
//
//==========================================================================================================================
		~Renderer(void){ };
		
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static Renderer* Instance(void);

		//void ShutDown(void);

//==========================================================================================================================
//
//Renderer Funtions
//
//==========================================================================================================================
		void SetBackgroundColor(color& c) { _programWindow->SetBackgroundColor(c); }

		void AddTri(const Cell& cell);
		
		void AddSqr(const Cell& cell);
		
		void AddHex(const Cell& cell);

		void AddTexturedTri(const Cell& cell, const Texture& texture);
		
		void AddTexturedSqr(const Cell& cell, const Texture& texture);
		
		void AddTexturedHex(const Cell& cell, const Texture& texture);
		
		void Draw(void);
		
	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		Renderer(void);
	};

}//End namespace

#endif