/*========================================================================
The Cell, or rendering cell is the basic Geometric perimitive that any
game object or entity that is to be rendered will have. It will be the 
OGL verticies that make up the position on the screen. While it will
never be called on its own, it will be part of the rendered game objects.

Based on which RenderAs* function is call, the cell is be rendered as the 
called primitive. The Cell is not responsible for setting this up, the 
Renderer is. The Cell will just need to get its position to the Renderer
and the Renderer will set up all the point for OGL, and will then store
them in a container until the scene is drawn. 

The Cell will also hold the texture information, once that is added to the
system. Basically it will hold all the data that needs to be given to the
Renderer in order for the Renderer to give that information to OGL. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/

#ifndef CELL_H
#define CELL_H

//=====Killer1 inlucdes=====
#include <Engine/Atom.h>
#include <Engine/Color.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Renderer.h>

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>

//=====STD includes=====
#include <vector>

namespace KillerEngine 
{

//=====Foreward delcaration=====
	class Renderer;

	class Cell 
	{	
		public:
//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
		Cell& operator=(const Cell& cell) 
		{
			
			return *this;
		}
		
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//=====Vertices=====		
		virtual void v_SetVertexPositions(const point& p, const F32 w, const F32 h) = 0;
		virtual void v_SetVertexColors( const color& c) = 0;
		virtual void v_SetVertexUvs(void) = 0;

//=====Position=====	
		void SetPosition(const point& p) 
		{ 
			_position = p; 
			v_SetVertexPositions(_position, _width, _height);
		}

		const point& GetPosition(void) const { return _position; }

		const F32* GetPositionArray(void) const { return _position.Get(); }
		
//=====Color=====		
		void SetColor(const color& c) 
		{ 
			_color = c; 
			v_SetVertexColors(_color);
		}

		const color& GetColor(void) const { return _color; }

		const F32* GetColorArray(void) const { return _color.Get(); }
		
//=====Width=====				
		void SetWidth(const F32 w) 
		{ 
			_width = w;
			v_SetVertexPositions(_position, _width, _height);
		}

		F32 GetWidth(void) { return _width; }

//=====Height=====
		void SetHeight(const F32 h) 
		{
			_height = h;
			v_SetVertexPositions(_position, _width, _height); 
		}

		F32 GetHeight(void) { return _height; }

//=====Width, Height=====
		void SetWidthHeight(const F32 w, const F32 h) 
		{
			_width = w;
			_height = h;
			v_SetVertexPositions(_position, _width, _height);
		}	

//==========================================================================================================================
//
//Cell Functions 	 	
//
//==========================================================================================================================
	protected:
		point     		 _position;
		color     		 _color;
		F32		  		 _width;
		F32		  		 _height;
		std::vector<F32> _vertexPositions;
		std::vector<F32> _vertexColors;
		std::vector<F32> _vertexUvs;

	private:	
		Renderer* 		 _renderer;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Cell(void);


	};
}//End namespace

#endif