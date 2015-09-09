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

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Texture.hpp>

//=====STL includes=====
#include <map>
using std::map;

//=====DevIL includes=====
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

namespace KillerEngine {

	class TextureManager{
	private:
		static TextureManager* _instance;
		ErrorManager*   	   _errorManager;
		Texture 			   _currentTexture;
		map<text, Texture>	   _loadedTextures;

	public:
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static TextureManager* Instance(void);
		void Shutdown(void);
		
//==========================================================================================================================
//
//TextureManager Functions
//
//==========================================================================================================================
		void LoadTexture(text path, text name);
		Texture& GetTexture(text name) { return _loadedTextures.find(name)->second; }

	protected:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		TextureManager(void);
		~TextureManager(void) {  }

	};
}//End namespace

#endif