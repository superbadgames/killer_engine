#include <TextManager.h>

//---------------------------------------------------------
//Instance
//---------------------------------------------------------
TextManager* TextManager::_instance = NULL;

TextManager* TextManager::Instance(void) {
	if(_instance == NULL) { _instance = new TextManager(); }
	return _instance;
}

//---------------------------------------------------------
//Init
//---------------------------------------------------------
void TextManager::Init(void) {
	FT_Error error = FT_Init_FreeType(&_library);
	if(error) { MessageBox(NULL, "Unable to initialize Library", "An Error occured", MB_ICONERROR | MB_OK); }

	error = FT_New_Face(_library, "C:\\Windows\\Fonts\\Arial", 0, &_font);
	if(error == FT_Err_Unknown_File_Format) { 
		MessageBox(NULL, "Unable to initialize FT New Face: Unkown File Format", "An Error occured", MB_ICONERROR | MB_OK); 
	}
	else if(error) { MessageBox(NULL, "Unable to initialize FT New Face", "An Error occured", MB_ICONERROR | MB_OK); }

	error = FT_Set_Char_Size(_font, 0, 16*64, 0, 72);
	//error = FT_Set_Pixel_Sizes(_font, width, height);


}