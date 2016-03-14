/*========================================================================
The Font class is used to open a .fnt file, extract the needed character
data, and then save that for text processing later on.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef FONT_H
#define FONT_H

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/Texture.hpp>
#include <Engine/SqrSprite.h>

//=====STL includes=====
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <map>
#include <list>

namespace KillerEngine
{
	struct CharacterData
	{
		U32 id;
		U32 x;
		U32 y;
		U32 width;
		U32 height;
		U32 xoffset;
		U32 yoffset;
		U32 xadvance;
	};

	class Font
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Font(void);

//==========================================================================================================================
//
//Font Functions
//
//==========================================================================================================================
		void InitFont(string fontName, string fontFile);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		std::list<SqrSprite&> CreateRenderText(string text);

		void SetFontFile(string fontFile) { _fontFile = fontFile; }

		string GetFontFile(void) 		  { return _fontFile; }

		void SetFontName(string fontName) { _fontName = fontName; }

		string GetFontName(void) 		  { return _fontName; }

		void SetFontTexture(const Texture& texture) { _texture = texture }

		Texture& GetFontTexture(void) { return _texture; }

	private:
		Texture& 					 _texture;
		string  					 _fontFile;
		string  					 _fontName;
		U32     					 _headerSize = 26;
		std::map<U32, CharacterData> _fontCharData;

		void _AddNewCharacterData(string id,      string x, 		string y,
							  	  string width,   string height,   string xoffset,
							  	  string yoffset, string xadvance);
	};
}

#endif