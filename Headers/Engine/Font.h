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
#include <Engine/TextureManager.h>

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
		Font(void);

		Font(Texture* texture);

//==========================================================================================================================
//
//Font Functions
//
//==========================================================================================================================
		void InitFont(string fontName, string fontFile);

		CharacterData* GetDataForCharacter(char c);

		std::map<U32, CharacterData*> GetDataMap(void) { return _fontCharData; }

		CharSprite* CreateCharacter(char character);

//==========================================================================================================================
//
//Operators
//
//==========================================================================================================================

		Font& operator=(Font* font)
		{
			_texture = font->GetTexture();
			_fontFile = font->GetFile();
			_fontName = font->GetName();
			_fontCharData = font->GetDataMap();

			return *this;
		}

		Font& operator=(Font& font)
		{
			_texture = font.GetTexture();
			_fontFile = font.GetFile();
			_fontName = font.GetName();
			_fontCharData = font.GetDataMap();

			return *this;
		}		

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void SetFile(string fontFile) 	  { _fontFile = fontFile; }

		string GetFile(void) 		  	  { return _fontFile; }

		void SetName(string fontName) 	  { _fontName = fontName; }

		string GetName(void) 		  	  { return _fontName; }

		void SetTexture(U32 textureID) { _texture = _textureManager->GetTexture(textureID); }

		Texture& GetTexture(void) 		  { return _texture; }

	private:
		Texture 					 _texture;
		string  					 _fontFile;
		string  					 _fontName;
		U32     					 _headerSize = 26;
		std::map<U32, CharacterData*> _fontCharData;
		TextureManager*				  _textureManager;

		void _AddNewCharacterData(string id,      string x, 		string y,
							  	  string width,   string height,   string xoffset,
							  	  string yoffset, string xadvance);
	};
}

#endif