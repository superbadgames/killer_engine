/*========================================================================
Sprite with 3 vertices. Used to make basic triangles. Will support a color
at first, and maybe later a texture. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef TRI_SPRITE_H
#define TRI_SPRITE_H

//=====Killer1 Includes=====
#include <Engine/Atom.h>
#include <Engine/Sprite.h>
#include <Engine/Renderer.h>

namespace KillerEngine
{
	class TriSprite : public Sprite
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		TriSprite(void);

		~TriSprite(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_RenderSprite(void);

		GLuint v_GetShader(void);

		void v_InitShader(void);

	private:
		static GLuint _shaderProgram;
		static const GLchar* _vertexShaderSource[];
		static const GLchar* _geometryShaderSource[];
		static const GLchar* _fragmentShaderSource[];

	};//end Class
}//end Namespace
#endif
