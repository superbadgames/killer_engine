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
			GLuint texture = i->second.GetId();
			glDeleteTextures(1, &texture);
		}
	}

//====================================================================================================
//
//TextureManager Functions
//
//=====================================================================================================
	void TextureManager::LoadTexture(text path, text name, S32 width, S32 height) {

		unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

		if(image == 0) {
			text errorMessage = text("SOIL_load_image failed to load image: ") + path;
			_errorManager->SetError(EC_TextureManager, errorMessage);
		}
		else {
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D( GL_TEXTURE_2D,		//target
						  0,					//first mipmap level
						  GL_RGBA,				//internal format
						  width, height,		//dimensions of texture
						  0,					//border
						  GL_RGBA,				//format
						  GL_UNSIGNED_BYTE,		//type
						  image 				//image data from SOIL
						 );
			glGenerateMipmap(GL_TEXTURE_2D);

			_loadedTextures[name] = new Texture(texture, width, height);

			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);

		}
	}

}//End namespace