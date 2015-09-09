#include <Engine/TextureManager.h>

namespace KillerEngine {

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
	TextureManager* TextureManager::_instance = NULL;
	TextureManager* TextureManager::Instance(void) {
		if(_instance == NULL) { _instance = new TextureManager(); }
		return _instance;
	}

	void TextureManager::Shutdown(void) {
		map<text, Texture>::iterator i;
		for(i = _loadedTextures.begin(); i != _loadedTextures.end(); ++i) {
			GLuint g = i->second.GetId();
			glDeleteTextures(1, &g);
		}
	}

//====================================================================================================
//
//TextureManager Functions
//
//=====================================================================================================
	void TextureManager::LoadTexture(text path, text name) {
		//ilutRenderer(ILUT_OPENGL);

		ILuint imageName;

		ilGenImages(1, &imageName);
		ilBindImage(imageName);
		

		if(!ilLoadImage(path.c_str())) { _errorManager->SetError(EC_DevIL, "ilLoadImage returned false"); }
		else {
			if(!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE)) { _errorManager->SetError(EC_DevIL, "ilConvertImage returned false"); }
			else {
				GLuint newTexture;
				glGenTextures(1, &newTexture);
				glBindTexture(GL_TEXTURE_2D, newTexture);

				glTexImage2D
				(
					GL_TEXTURE_2D,					//target 
					0, 								//first mipmap level
					ilGetInteger(IL_IMAGE_BPP), 	//internal format
					ilGetInteger(IL_IMAGE_WIDTH),	//width
	     			ilGetInteger(IL_IMAGE_HEIGHT),  //height
	     			0, 								//border
	     			ilGetInteger(IL_IMAGE_FORMAT),  //format
	     			GL_UNSIGNED_BYTE,				//type
	     			ilGetData()						//date pointer
	     		);

	     		_loadedTextures[name] = new Texture(newTexture, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));
			}
		}

		ilDeleteImages(1, &imageName);
	}

//====================================================================================================
//
//Constructor
//
//=====================================================================================================
	TextureManager::TextureManager(void) : _errorManager(ErrorManager::Instance())
	{
		ilInit();
		iluInit();
		ilutRenderer(ILUT_OPENGL);
	}

}//End namespace