/*=========================================================================
The TextureManager is a singleton class that will controll when and how all
textures are added to memory from the disc. In order to make this process 
as easy as possible the functions written to control how this works uses
the DevIL library. See http://openil.sourceforge.net/about.php for details.

DevIL uses the GNU liscense, which is included in the documentation for 
reference. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
=========================================================================*/
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>


class TextureManager{
private:
	static TextureManager* _instance;

	ErrorManager* _errorManager;

public:
	static TextureManager* Instance();
	void AddImage();

protected:
	TextureManager(void);
	~TextureManager(void) {  }

};

#endif