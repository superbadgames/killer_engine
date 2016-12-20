/*========================================================================
This class will hold all the data for a string of text that will be drawn
to the screen. It will use the font class and the texture manager to keep
track of all the character data and the texture for the font. 

It is considered a GameObject2D, and when adding it to the work it should
be treated as any other GameObject2D.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef RENDER_TEXT_H
#define RENDER_TEXT_H

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/Font.h>
#include <Engine/CharSprite.h>

//=====STL includes=====
#include <vector>

namespace KillerEngine
{
	class RenderText : public GameObject2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		RenderText(void);

		RenderText(Font& font);
		
		RenderText(string text, Font& font);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Update(void);

		void v_Render(void);

//==========================================================================================================================
//
//RenderText Functions
//
//==========================================================================================================================		
		void AddText(string text);

		void SetTextPosition(Vec2& pos);

		void SetWidthScaleFactor(F32 w) { _widthScaleFactor = w; }

		void SetHeightScaleFactor(F32 h) { _heightScaleFactor = h; }

		void SetScaleFactors(const F32 w, const F32 h) { _widthScaleFactor = w; _heightScaleFactor = h; }

		void SetFont(Font& font) { _font = font; }

		F32 GetTotalWidth(void) { return _totalWidth; }

		F32 GetTotalHeight(void) { return _totalHeight; }

		Vec2& GetCenter(void) { return _center; }

	private:
		string _text;
		Font   _font;
		std::vector<CharSprite*> _spriteList;
		F32 _widthScaleFactor;
		F32 _heightScaleFactor;
		F32 _totalWidth;
		F32 _totalHeight;
		Vec2 _center;	
	};
}

#endif