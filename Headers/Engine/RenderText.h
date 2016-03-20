/*========================================================================
This class will hold all the data for a string of text that will be drawn
to the screen. It will use the font class and the texture manager to keep
track of all the character data and the texture for the font. 

It is considered a GameObject, and when adding it to the work it should
be treated as any other GameObject.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef RENDER_TEXT_H
#define RENDER_TEXT_H

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.hpp>
#include <Engine/Font.h>
#include <Engine/CharSprite.h>

//=====STL includes=====
#include <vector>

namespace KillerEngine
{
	class RenderText : public GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		RenderText(void);

		RenderText(Font* font);
		
		RenderText(string text, Font* font);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Update(void) {  }

		void v_Render(void);

//==========================================================================================================================
//
//RenderText Functions
//
//==========================================================================================================================		
		void AddText(string text);

		void SetFont(Font* font) { _font = font; }

	private:
		string _text;
		Font*   _font;
		std::vector<CharSprite*> _spriteList;
	};
}

#endif