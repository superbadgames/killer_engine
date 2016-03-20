/*=========================================================================
The Texture struct is used to save and hold information about a texture that
has already been loaded into memory. It is there to save the GLUINT ID that 
is returned from DevIL that represents the saved texture that is fully loaded
into memory. 


This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
=========================================================================*/
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

//=====OGL includes=====


namespace KillerEngine 
{

	class Texture 
	{
	private:	
		GLuint _id;
		S32    _width;
		S32    _height;

	public:	
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Texture(void) : _id(0), _width(0), _height(0) {  }

		Texture(GLuint id, S32 width, S32 height) : _id(id), _width(width), _height(height) {  }

		Texture(const Texture& T) : _id(T.GetId()), _width(T.GetWidth()), _height(T.GetHeight()) {  }

		Texture(const Texture* T) : _id(T->GetId()), _width(T->GetWidth()), _height(T->GetHeight()) {  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		GLuint GetId(void) const { return _id; }

		void SetId(GLuint id) { _id = id; }

		S32 GetWidth(void) const { return _width; }

		void SetWidth(S32 w) { _width = w; }

		S32 GetHeight(void) const { return _height; }

		void SetHeight(S32 h) { _height = h; }

//==========================================================================================================================
//
//Operator Overload
//
//==========================================================================================================================
		Texture& operator=(const Texture& T) 
		{
			_id     = T.GetId();
			_width  = T.GetWidth();
			_height = T.GetHeight();

			return *this;
		}

		Texture& operator=(Texture* T)
		{
			_id     = T->GetId();
			_width  = T->GetWidth();
			_height = T->GetHeight();

			return *this;
		}

	};

}


#endif