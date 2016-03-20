/*========================================================================
The Sprite, or rendering cell is the basic Geometric perimitive that any
game object or entity that is to be rendered will have. It will be the 
OGL verticies that make up the position on the screen. While it will
never be called on its own, it will be part of the rendered game objects.

Based on which RenderAs* function is call, the cell is be rendered as the 
called primitive. The Sprite is not responsible for setting this up, the 
Renderer is. The Sprite will just need to get its position to the Renderer
and the Renderer will set up all the Vec for OGL, and will then store
them in a container until the scene is drawn. 

The Sprite will also hold the texture information, once that is added to the
system. Basically it will hold all the data that needs to be given to the
Renderer in order for the Renderer to give that information to OGL. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/

#ifndef SPRITE_H
#define SPRITE_H

//=====Killer1 inlucdes=====
#include <Engine/Atom.h>
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

	class Sprite 
	{	
		public:
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
			void SetWidth(F32 w)  { _width = w; }

			F32 GetWidth(void)    { return _width; }

			void SetHeight(F32 h) { _height = h; }

			F32 GetHeight(void)   { return _height; }			

			Vec2& GetPosition(void) { return _position; }

			Col& GetColor(void) { return _color; }

			Texture& GetTexture(void) { return _texture; }
 
//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
		Sprite& operator=(Sprite& sprite) 
		{
			_width = sprite.GetWidth();
			_height = sprite.GetHeight();
			SetPosition(sprite.GetPosition());
			SetColor(sprite.GetColor());

			return *this;
		}
		
//==========================================================================================================================
//
//Virtual
//
//==========================================================================================================================
		virtual void v_RenderSprite(void)=0;

		//virtual void v_RenderSprite(const Vec& pos, F32 w, F32 h, const Col& col, const Texture& tex) {  }

		virtual void SetPosition(Vec2& position)=0;

		virtual void SetColor(Col& col)=0;

		virtual void SetTexture(Texture& texture, const F32 top, const F32 bottom, const F32 right, const F32 left)=0;

//==========================================================================================================================
//
//Sprite Functions 	 	
//
//==========================================================================================================================

	protected:
		Renderer* 		 _renderer;
		std::vector<F32> _vertexPositions;
		std::vector<F32> _vertexColors;
		std::vector<F32> _vertexUvs;
		F32				 _width;
		F32				 _height;
		Vec2			 _position;
		Col			 	 _color;
		Texture	    	 _texture;
		

		virtual void v_SetVertexPositions(void) = 0;
		//virtual void v_SetVertexData(const Vec& p, const F32 w, const F32 h, const color& col) = 0;
		
		virtual void v_SetVertexColors(void) = 0;
		
		virtual void v_SetTextureCoords(const F32 top, const F32 bottom, const F32 right, const F32 left) = 0;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Sprite(void);

		Sprite(const F32 width, const F32 height);

		Sprite(const F32 width, const F32 height, Col& col);

		Sprite(const F32 width, const F32 height, Texture& texture);

		Sprite(const F32 width, const F32 height, Col& col, Texture& texture);

	};
}//End namespace

#endif