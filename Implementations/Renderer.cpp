#include <Engine/Renderer.h>
#include <iostream>

namespace KillerEngine 
{

//==========================================================================================================================
//
//Private Renderer Functions
//
//==========================================================================================================================
//=======================================================================================================
//_SetOrthoProjection
//=======================================================================================================
	void Renderer::_SetOrthoProjection(void) 
	{
		Matrix projection{};
		projection.MakeOrthographic((F32)WinProgram::Instance()->GetWidth(), (F32)WinProgram::Instance()->GetHeight(), 200);

		Matrix model(1.0f);

		Matrix final = projection * model;

		const F32* data = final.GetElems();

		GLint transform1 = glGetUniformLocation(_currentShader, "transform_mat");

		glUniformMatrix4fv(transform1, 1, GL_FALSE, data);
	}

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
//=======================================================================================================
//Instance
//=======================================================================================================
	Renderer* Renderer::_instance = NULL;

	Renderer* Renderer::Instance(void) 
	{
		if(_instance == NULL) { _instance = new Renderer(); }
		return _instance;
	}

//=======================================================================================================
//ShutDown
//=======================================================================================================
	/*void Renderer::ShutDown(void) {
		delete _instance;
		glDeleteVertexArrays(1, &_vertexArrayObject);
		glDeleteProgram(_renderingProgram);
		glDeleteVertexArrays(1, &_vertexArrayObject);
	}*/


//=======================================================================================================
//AddToBatch
//=======================================================================================================
	void Renderer::AddToBatch(GLuint shader, Vec2& pos, F32 w, F32 h, Col& c)
	{
		if(_currentShader != shader)
		{
			Draw();
			_currentShader = shader;

			glUseProgram(_currentShader);

			//_SetOrthoProjection();
			Camera::Instance()->SetUp(shader);
		}

		if(_currentBatchSize + 1 >= _maxBatchSize) { Draw(); }

		_vertices.push_back(pos.GetX());
		_vertices.push_back(pos.GetY());
		_vertices.push_back(pos.GetZ());
		_vertices.push_back(pos.GetW());
		
		_dimensions.push_back(w/2);
		_dimensions.push_back(h/2);

		_colors.push_back(c.GetRed());
		_colors.push_back(c.GetGreen());
		_colors.push_back(c.GetBlue());
		_colors.push_back(c.GetAlpha());
		
		++_currentBatchSize;
	}

	void Renderer::AddToBatch(GLuint shader, Vec2& pos, F32 w, F32 h, Col& c, U32 textureID)
	{
		if(TextureManager::Instance()->GetCurrentTextureID() != textureID)
		{
			Draw();
			TextureManager::Instance()->SetCurrentTextureID(textureID);
		}

		_bottomTop.push_back(0.0f);
		_bottomTop.push_back(0.0f);
		_leftRight.push_back(1.0f);
		_leftRight.push_back(1.0f);
		AddToBatch(shader, pos, w, h, c);
	}

	void Renderer::AddToBatch(GLuint shader, Vec2& pos, F32 w, F32 h, Col& c, U32 textureID, Vec2& origin, Vec2& limit)
	{
		
		if(TextureManager::Instance()->GetCurrentTextureID() != textureID)
		{
			Draw();
			TextureManager::Instance()->SetCurrentTextureID(textureID);
		}
		
		_bottomTop.push_back(origin.GetX());
		_bottomTop.push_back(origin.GetY());
		_leftRight.push_back(limit.GetX());
		_leftRight.push_back(limit.GetY());
		AddToBatch(shader, pos, w, h, c);
	}

//=======================================================================================================
//Draw
//=======================================================================================================

	void Renderer::Draw(void)
	{
		if(_currentBatchSize == 0) return;

		GLuint buffers[5];
		glGenBuffers(5, buffers);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _vertices.size()), &_vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _colors.size()), &_colors[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _dimensions.size()), &_dimensions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		if(_bottomTop.size() > 0)
		{
			
			glEnable (GL_BLEND); 
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _bottomTop.size()), &_bottomTop[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	
			glBindBuffer(GL_ARRAY_BUFFER, buffers[4]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _leftRight.size()), &_leftRight[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		}
		
		glDrawArrays(GL_POINTS, 0, _currentBatchSize);

		//=====Reset All Containers and Counters=====
		_vertices.clear();
		_dimensions.clear();
		_colors.clear();
		_bottomTop.clear();
		_leftRight.clear();
		_currentBatchSize = 0;
	}
//=======================================================================================================
//
//Constructor
//
//=======================================================================================================
	Renderer::Renderer(void): _maxBatchSize(1000), 
							  _currentBatchSize(0)
	{ 
		glGenVertexArrays(1, &_vertexArrayObject);
		glBindVertexArray(_vertexArrayObject);
	}

}//End namespace		