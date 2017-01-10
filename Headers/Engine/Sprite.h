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

//=====Typedef=====
typedef std::vector<F32> Array;

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
			void SetWidth(F32 w)  { width = w; }

			F32 GetWidth(void)    { return width; }

			void SetHeight(F32 h) { height = h; }

			F32 GetHeight(void)   { return height; }

			void SetDimensions(F32 w, F32 h) { width = w; height = h; }			

			void SetPosition(Vec2& pos) { position = pos; }

			Vec2& GetPosition(void) { return position; }

			void SetColor(Col& col) { color = col; }

			Col& GetColor(void) { return color; }

			U32 GetTextureID(void) { return textureID; }

			void SetVertices(Array vertices) { vertexPositions = vertices; }

			Array GetVertices(void) { return vertexPositions; }

			void SetVertexColors(Array colors) { vertexColors = colors; }

			Array GetVertexColors(void) { return vertexColors; }

			Array GetVertexUvs(void) { return vertexUvs;}


 
//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
		Sprite& operator=(Sprite& sprite) 
		{
			width = sprite.GetWidth();
			height = sprite.GetHeight();
			v_SetPosition(sprite.GetPosition());
			v_SetColor(sprite.GetColor());

			return *this;
		}
		
//==========================================================================================================================
//
//Virtual
//
//==========================================================================================================================
		virtual void v_RenderSprite(void)=0;

		//virtual void v_RenderSprite(const Vec& pos, F32 w, F32 h, const Col& col, const U32 tex) {  }

		virtual void v_SetPosition(Vec2& position)=0;

		virtual void v_SetColor(Col& col)=0;

		virtual void v_SetTexture(U32 tID, const F32 top, const F32 bottom, const F32 right, const F32 left)
		{
			textureID = tID;

			v_SetTextureCoords(top, bottom, left, right);
		}

//==========================================================================================================================
//
//Sprite Functions 	 	
//
//==========================================================================================================================

	protected:
		Array vertexPositions;
		Array vertexColors;
		Array vertexUvs;
		F32				 width;
		F32				 height;
		U32				 textureID;
		Vec2			 position;
		Col			 	 color;
		
		

		virtual void v_SetVertexPositions(void) = 0;
		
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

		Sprite(const F32 width, const F32 height, U32 tID);													     

		Sprite(const F32 width, const F32 height, Col& col, U32 tID);																   

	};
}//End namespace

#endif