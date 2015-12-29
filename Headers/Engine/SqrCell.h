/*========================================================================
Subclass of the cell. Used to provide implemenation specific information 
for the specific shape of a square. 

_vertexPosition : This std::vector will contain all of the point that make up a square. 

Here is how the points are found: 

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

#ifndef SQRCELL_H
#define SQRCELL_H

//=====Killer1 Includes=====
#include <Engine/Atom.h>
#include <Engine/Cell.h>
#include <Engine/Texture.hpp>
#include <Engine/TextureManager.h>

namespace KillerEngine
{
	class SqrCell: public Cell
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================		
		SqrCell(void);

//==========================================================================================================================
//
//Virtual Functions 	 	
//
//==========================================================================================================================
		void v_RenderCell(const point& pos, F32 w, F32 h, const color& col);

		void RenderTexture(const point& pos, F32 w, F32 h, const color& colo, Texture& tex);

		void v_SetVertexPositions(const point& p, const F32 w, const F32 h);
		
		void v_SetVertexColors( const color& c);
		
		void v_SetVertexUvs(void);

	private:
		TextureManager* _textureManager;

	};
}


#endif