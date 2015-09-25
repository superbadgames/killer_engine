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

namespace KillerEngine 
{

//=====Foreward delcaration=====
	class Renderer;

	class Cell 
	{	
	private:	
		Renderer* _renderer;
		point     _position;
		color     _color;

		F32 _totalWidth;
		F32	_right;
		F32	_left;
		
		F32	_totalHeight;
		F32	_top;
		F32 _bottom;

	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Cell(void);
		
		Cell(const F32 w, const F32 h);
		
		Cell(const F32 w, const F32 h, const point& p, const color& c);
		
		Cell(const Cell& cell);

		~Cell(void){  }

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
		Cell& operator=(const Cell& cell) 
		{
			_position = cell.GetPosition();
			_color 	  = cell.GetColor();
			SetDimensions(cell.GetWidth(), cell.GetHeight());

			return *this;
		}
		
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void SetPosition(const point& p) { _position = p; }
		
		void SetColor(const color& c)    { _color = c; }
		
		void SetWidth(const F32 w) 
		{
			_totalWidth = w;
			_right 		= w / 2;
			_left  		= -w / 2;
		}

		void SetHeight(const F32 h) 
		{
			_totalHeight = h;
			_top 		 = h / 2;
			_bottom 	 = -h / 2;
		}

		void SetDimensions(const F32 w, const F32 h) 
		{
			SetWidth(w);
			SetHeight(h);
		}

		const point& GetPosition(void) const { return _position; }
		
		const F32*   GetPositionArray(void) const { return _position.Get(); }
		
		const color& GetColor(void) const { return _color; }
		
		const F32* GetColorArray(void) const { return _color.Get(); }
		
		const F32 GetWidth(void) const { return _totalWidth; }
		
		const F32 GetRight(void) const { return _right; }
		
		const F32 GetLeft(void) const { return _left; }
	 	
	 	const F32 GetHeight(void) const { return _totalHeight; }
	 	
	 	const F32 GetTop(void) const { return _top; }
	 	
	 	const F32 GetBottom(void) const { return _bottom; }

//==========================================================================================================================
//
//Cell Functions 	 	
//
//==========================================================================================================================

		void RenderAsTri(void);
		
		void RenderAsSqr(void);
		
		void RenderAsHex(void);
		
		void RenderTexturedTri(const Texture& texture);
		
		void RenderTexturedSqr(const Texture& texture);
		
		void RenderTexturedHex(const Texture& texture);
	};
}//End namespace

#endif