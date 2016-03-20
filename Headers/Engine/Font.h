/*========================================================================
The Font class is used to open a .fnt file, extract the needed character
data, and then save that for text processing later on.

CreateCharacter is a CharSprite Factory. This may be important to know.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef FONT_H
#define FONT_H

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/Texture.hpp>
#include <Engine/CharSprite.h>

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
		F32 x;
		F32 y;
		F32 width;
		F32 height;
		F32 xoffset;
		F32 yoffset;
		F32 xadvance;
	};

	//Forward declare CharSprite
	class CharSprite;

	class Font
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Font(Texture* texture);

//==========================================================================================================================
//
//Font Functions
//
//==========================================================================================================================
		void InitFont(string fontName, string fontFile);

		CharacterData* GetDataForCharacter(char c);

		CharSprite* CreateCharacter(char character);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void SetFontFile(string fontFile) { _fontFile = fontFile; }

		string GetFontFile(void) 		  { return _fontFile; }

		void SetFontName(string fontName) { _fontName = fontName; }

		string GetFontName(void) 		  { return _fontName; }

		void SetFontTexture(Texture& texture) { _texture = texture; }

		Texture& GetTexture(void) { return _texture; }

	private:
		Texture 					 _texture;
		string  					 _fontFile;
		string  					 _fontName;
		U32     					 _headerSize = 26;
		std::map<U32, CharacterData*> _fontCharData;

		void _AddNewCharacterData(string id,      string x, 		string y,
							  	  string width,   string height,   string xoffset,
							  	  string yoffset, string xadvance);
	};
}

#endif