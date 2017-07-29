#include <Engine/Camera.h>

namespace KillerEngine
{
//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================
	Camera* Camera::_instance = NULL;

	Camera* Camera::Instance(void)
	{
		if(_instance == NULL) { _instance = new Camera(); }
		return _instance;
	}

	void Camera::SetUp(GLuint shader)
	{
		
		//temporary fix to get camera working for now. 
		const F32* data = _projection.GetElems();

		GLint transform1 = glGetUniformLocation(shader, "perspective_mat");

		glUniformMatrix4fv(transform1, 1, GL_FALSE, data);

		const F32* data2 = _translation.GetElems();

		GLint transform2 = glGetUniformLocation(shader, "modelView_mat");

		glUniformMatrix4fv(transform2, 1, GL_FALSE, data2);

/*	
		//not working matrix multiplication. Will fix later
		//_translation = _projection * _translation;
		_translation *= _projection;
		
		const F32* data = _translation.GetElems();

		GLint transform1 = glGetUniformLocation(shader, "transform_mat");

		glUniformMatrix4fv(transform1, 1, GL_FALSE, data);
*/		
	}

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Camera::Camera(void) : _background(1.0f), _projection(), _translation(1.0f)
	{
		_projection.MakeOrthographic((F32)WinProgram::Instance()->GetWidth(), (F32)WinProgram::Instance()->GetHeight(), 200);
	}	
}//end namespace