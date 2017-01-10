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
		void v_RenderSprite(void) { Renderer::Instance()->AddToBatch(Sprite::GetVertices(), Sprite::GetVertexColors()); }

		void v_SetVertexPositions(void);
		
		void v_SetVertexColors(void);
		
		void v_SetTextureCoords(const F32 top, const F32 bottom, const F32 right, const F32 left) {  }

		void v_SetPosition(Vec2& position);

		void v_SetColor(Col& col);

	};//end Class
}//end Namespace
#endif
