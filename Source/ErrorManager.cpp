#include <ErrorManager.h>
//============================================================================================
//Instance
//============================================================================================
ErrorManager* ErrorManager::_instance = NULL;

ErrorManager* ErrorManager::Instance(void) {
	if(_instance == NULL) { _instance = new ErrorManager(); }
	return _instance;
}

//============================================================================================
//SetError
//============================================================================================
void ErrorManager::SetError(ErrorCode code, string message) {
	_errorCode 	  = code;
	_errorMessage = message;
}

//============================================================================================
//DisplayError
//============================================================================================
void ErrorManager::DisplayError(void) {
	switch(_errorCode) {
		case EC_NoError: {
			//later, it will print to a log file, maybe
		}
		case EC_Unknown: {
			MessageBox(NULL, _errorMessage.c_str(), "UNKNOWN", MB_ICONERROR | MB_OK); 
			break;
		}
		case EC_KillerEngine: {
			MessageBox(NULL, _errorMessage.c_str(), "KILLER_ENGINE", MB_ICONERROR | MB_OK);
			break;
		}
		case EC_Windows: {
			MessageBox(NULL, _errorMessage.c_str(), "WINDOWS", MB_ICONERROR | MB_OK);
			break;
		}
		case EC_OpenGL: {
			MessageBox(NULL, _errorMessage.c_str(), "OPENGL", MB_ICONERROR | MB_OK);
			break;
		}
		case EC_DirectInput: {
			MessageBox(NULL, _errorMessage.c_str(), "DIRECT_INPUT", MB_ICONERROR | MB_OK);
			break;
		}
		default: break;
	}
}