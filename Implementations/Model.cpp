#include <Engine/Model.h>

namespace KillerEngine
{
//==========================================================================================================================
//Static Member init
//==========================================================================================================================
	GLuint Model::_shaderProgram = NULL;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Model::Model(void) : _vertices()
	{  }

	Model::Model(std::vector<F32> vertices) : _vertices(vertices)
	{

	}

	Model::Model(F32* verticeArray, U32 length) : _vertices(verticeArray, verticeArray + length)
	{  }

	Model::~Model(void)
	{  }
}//end namespace