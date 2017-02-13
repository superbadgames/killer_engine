#include <Engine/TextureManager.h>
#include <iostream>

namespace KillerEngine 
{

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
	TextureManager* TextureManager::_instance = NULL;
	
	TextureManager* TextureManager::Instance(void) 
	{
		if(_instance == NULL) 
			{ _instance = new TextureManager(); }
		
		return _instance;
	}

	void TextureManager::Shutdown(void) 
	{
		map<U32, Texture>::iterator i;
		
		for(i = _loadedTextures.begin(); i != _loadedTextures.end(); ++i) 
		{
			GLuint texture = i->second.GetID();
			glDeleteTextures(1, &texture);
		}
	}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	void TextureManager::SetCurrentTextureID(U32 tID)
	{ 
		_currentTextureID = tID; 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _loadedTextures[tID].GetID());
	}

//====================================================================================================
//
//TextureManager Functions
//
//=====================================================================================================
	void TextureManager::LoadTexture(string path, U32 id, S32 width, S32 height) 
	{
		if(_loadedTextures.find(id) != _loadedTextures.end())
		{
			std::cout << "TExture already loaded " << path << '\n';
			return;
		}

		unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

		if(image == 0) 
		{
			string errorMessage = string("SOIL_load_image failed to load image: ") + path;
			ErrorManager::Instance()->SetError(EC_TextureManager, errorMessage);
		}
		
		else 
		{
			GLuint glTexture;
			glGenTextures(1, &glTexture);
			glBindTexture(GL_TEXTURE_2D, glTexture);

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

			Texture* newTexture = new Texture(glTexture, width, height);

			_loadedTextures.insert(std::map<U32, Texture*>::value_type(id, newTexture));

			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);

		}
	}

}//End namespace