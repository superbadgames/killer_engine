/*========================================================================
This class will be a singleton that will controll all text that is 
drawn to the screen. It was built using FreeType 2, which was developed
under the GNU Public License, Version 2. 
http://www.freetype.org/freetype2/docs/index.html for more info.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/

#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

//Killer1 Engine include
#include <Atom.h>

//FreeType includes
#include <ft2build.h>
#include FT_FREETYPE_H

class TextManager{
private:
	FT_Library _library;
	FT_Face	   _font;

	static TextManager* _instance;

public:
	static TextManager* Instance(void);

	void Init(void);

protected:
	TextManager(void){}

};

#endif