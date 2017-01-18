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

		CharSprite(U32 x, U32 y, U32 width, U32 height, U32 xoffset, U32 yoffset, U32 xadvance);

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
		void SetCharID(U32 id)          { _charID = id; }

		U32 GetCharX(void) 				{ return _charX; }

		void SetCharX(U32 x) 			{ _charX =  x; }

		U32 GetCharY(void) 				{ return _charY; }

		void SetCharY(U32 y) 			{ _charY =  y; }

		U32 GetCharWidth(void) 		{ return _charWidth; }

		void SetCharWidth(U32 w) 	{ _charWidth =  w; }

		U32 GetCharHeight(void) 	{ return _charHeight; }

		void SetCharHeight(U32 h) 	{ _charHeight =  h; }

		U32 GetXOffset(void) 		{ return _xoffset; }

		void SetXOffset(U32 x) 		{ _xoffset =  x; }

		U32 GetYOffset(void) 		{ return _yoffset; }

		void SetYOffset(U32 y) 		{ _yoffset =  y; }

		U32 GetXAdvance(void) 		{ return _xadvance; }

		void SetXAdvance(U32 x) 	{ _xadvance =  x; }

//==========================================================================================================================
//
//Virtual Functions 	 	
//
//==========================================================================================================================
		void v_RenderSprite(void);

		void v_SetVertexPositions(void);
		
		void v_SetVertexColors(void);
		
		void v_SetTextureCoords(const F32 top, const F32 bottom, const F32 right, const F32 left);

		void v_SetPosition(Vec2& position);

		void v_SetColor(Col& col);

		GLuint v_GetShader(void);

		void v_InitShader(void);


	private:
		U32 				_charID;
		U32 				_charX;
		U32 				_charY;
		U32 				_charWidth;
		U32 				_charHeight;
		U32 				_xoffset;
		U32 				_yoffset;
		U32 				_xadvance;
	};
}

#endif