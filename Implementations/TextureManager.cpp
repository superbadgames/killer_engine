#include <Engine/TextureManager.h>

//====================================================================================================
//
//Static Member re-declarations
//
//=====================================================================================================
TextureManager* TextureManager::_instance = NULL;


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

//====================================================================================================
//
//Instance
//
//=====================================================================================================
TextureManager* TextureManager::Instance(void) {
	if(_instance == NULL) { _instance = new TextureManager(); }
	return _instance;
}

//====================================================================================================
//
//AddImage
//
//=====================================================================================================
void TextureManager::AddImage(void) {
	//ilutRenderer(ILUT_OPENGL);

	ILuint imageName;

	ilGenImages(1, &imageName);
	ilBindImage(imageName);
	
	const char* filepath = "../Assets/first_box.png";

	if(!ilLoadImage(filepath)) { _errorManager->SetError(EC_DevIL, "ilLoadImage returned false"); }
	else {
		if(!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE)) { _errorManager->SetError(EC_DevIL, "ilConvertImage returned false"); }
		else {
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

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
		}
	}

	ilDeleteImages(1, &imageName);
}