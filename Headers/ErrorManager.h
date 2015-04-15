/*--------------------------------------------------------------------
A singleton class that will display any errors that can happen during
the initialization of any of the components of the engine. It will be
flushed out later to include more details. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
----------------------------------------------------------------------*/
#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

//Killer1 Includes
#include <Atom.h>

//Error Codes Enum
enum ErrorCode {
	EC_NoError = 0,
	EC_Unknown,
	EC_KillerEngine,
	EC_Windows,
	EC_OpenGL,
	EC_DirectInput
};

class ErrorManager {
private:
	ErrorCode _errorCode;
	string    _errorMessage;

	static ErrorManager* _instance;

public:
	~ErrorManager(void) {  }

	static ErrorManager* Instance(void);

	void SetError(ErrorCode code, string message);
	void DisplayError(void);

protected:
	ErrorManager(void) {  }
};

#endif