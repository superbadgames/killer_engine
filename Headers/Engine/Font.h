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

//=====STL includes=====
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

namespace KillerEngine
{
	class Font
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Font(void);

		Font(string fontName);

		Font(string fontName, string fontFile);

//==========================================================================================================================
//
//Font Functions
//
//==========================================================================================================================
		void CreateFont(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void SetFontFile(string fontFile) { _fontFile = fontFile; }

		string GetFontFile(void) 		  { return _fontFile; }

		void SetFontName(string fontName) { _fontName = fontName; }

		string GetFontName(void) 		  { return _fontName; }

	private:
		string _fontFile;

		string _fontName;

		U32    _headerSize = 26;

	};
}

#endif