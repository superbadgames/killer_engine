/*========================================================================
Subclass of the cell. Used to provide implemenation specific information 
for the specific shape of a square. 

_vertexPosition : This std::vector will contain all of the Vec that make up a square. 

Here is how the Vecs are found: 

Position = Place in the world. 
Widht = length of the x axis.
Height = length of the y axis.

Vertext Positions: 

There are 6 vertices. The square is made up of two triangle. They are
as follow: 

triangle 1: top right, bottom right, bottom left
triangle 2: top right, top left, bottom left

Vertex locaitons

top right = (1/2 Width, 1/2 Height)
bottom right = (1/2 Width, -1/2 Height)
top left = (-1/2 Width, 1/2 Height)
bottom left = (-1/2 Width, -1/2 Height)

Colors:
There are 1 color per vertex, each color represented by 4 F32 numbers 

Uvs:
There are 6 Uvs, one pair of numbers per vertex. It must follow the same pattern as the 
vertex positions above. Here are the exact coordinates needed for each vertex:

top right = (1.0, 1.0)
bottom right = (1.0, 0.0)
top left = (0.0, 1.0f)
bottom left = (0.0, 1.0)

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef CHAR_SPRITE_H
#define CHAR_SPRITE_H

//=====Killer1 Includes=====
#include <Engine/Atom.h>
#include <Engine/Sprite.h>
#include <Engine/Texture.hpp>
#include <Engine/TextureManager.h>
#include <Engine/Font.h>

namespace KillerEngine
{
	//Forward declar font
	class Font;

	class CharSprite: public Sprite
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================		
		CharSprite(void);

		CharSprite(F32 x, F32 y, F32 width, F32 height, F32 xoffset, F32 yoffset, F32 xadvance);

//==========================================================================================================================
//
//CharSprite Accessors
//
//==========================================================================================================================


//==========================================================================================================================
//
//CharacterData Accessors
//
//==========================================================================================================================		
		F32 GetX(void) 			{ return _x; }

		void SetX(F32 x) 		{ _x =  x; }

		F32 GetY(void) 			{ return _y; }

		void SetY(F32 y) 		{ _y =  y; }

		F32 GetWidth(void) 		{ return _width; }

		void SetWidth(F32 w) 	{ _width =  w; }

		F32 GetHeight(void) 	{ return _height; }

		void SetHeight(F32 h) 	{ _height =  h; }

		F32 GetXOffset(void) 	{ return _xoffset; }

		void SetXOffset(F32 x) 	{ _xoffset =  x; }

		F32 GetYOffset(void) 	{ return _yoffset; }

		void SetYOffset(F32 y) 	{ _yoffset =  y; }

		F32 GetXAdvance(void) 	{ return _xadvance; }

		void SetXAdvance(F32 x) { _xadvance =  x; }

//==========================================================================================================================
//
//Virtual Functions 	 	
//
//==========================================================================================================================
		void v_RenderSprite(void);

		void v_SetVertexPositions(void);
		
		void v_SetVertexColors(void);
		
		void v_SetTextureCoords(const F32 top, const F32 bottom, const F32 right, const F32 left);

		void SetPosition(Vec2& position);

		void SetColor(Col& col);

		void SetTexture(Texture& texture, const F32 top, const F32 bottom, const F32 right, const F32 left);

	private:
		TextureManager* 	_textureManager;
		F32 				_id;
		F32 				_x;
		F32 				_y;
		F32 				_width;
		F32 				_height;
		F32 				_xoffset;
		F32 				_yoffset;
		F32 				_xadvance;
	};
}

#endif