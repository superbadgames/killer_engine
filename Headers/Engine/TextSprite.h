/*========================================================================
Subclass of the cell. Used to provide implemenation specific information 
for the specific to a string of text that will be rendered to the screen.

Each text is going to be a square cell in shape, and will have the UV's 
to a specific character in a font that will act as a guide to set up each
character in the text string.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/

#ifndef TEXT_SPRITE_H
#define TEXT_SPRITE_H

//=====Killer1 Includes=====
#include <Engine/Atom.h>
#include <Engine/Sprite.h>
#include <Engine/Texture.hpp>
#include <Engine/TextureManager.h>

namespace KillerEngine
{
	class TextSprite : public Sprite
	{
	public:
		TextSprite(void);

		void SetCharacterData(const F32 u, const F32 v, const F32 w, const F32 h);

	private:
		F32 _u;
		F32 _v;
		F32 _width;
		F32 _height;
		TextureManager* _textureManager;

		void v_RenderSprite(const point& pos, F32 w, F32 h, const color& col) {  }

		void TextSprite::v_RenderSprite(const point& pos, F32 w, F32 h, const color& col, const Texture& tex);

		void v_SetVertexPositions(const point& p, const F32 w, const F32 h);

		void v_SetVertexColors( const color& col);

		void v_SetVertexUvs(void) {  }

		void v_SetVertexUvs(const Texture& tex);
	};
}

#endif