#include <Engine/Renderer.h>

namespace KillerEngine 
{

//==========================================================================================================================
//
//Private Renderer Functions
//
//==========================================================================================================================
//=======================================================================================================
//_CompileShaders
//=======================================================================================================
	void Renderer::_CompileShaders(void)
	{
		//=====Vertex Shaders=====
		//=====Color Shader=====
		//This is used when only colors, not textures are used to render
		//a pirmitive
		static const GLchar* _vertexShaderSourceColor[] = 
		{
			"#version 430 core																\n"
			"																				\n"
			"layout (location = 0) in vec4 position;										\n"
			"layout (location = 1) in vec4 color; 										\n"					
			"uniform mat4 transform_mat;													\n"
			"																				\n"
			"out vec4 vs_color;															\n"
			"																				\n"
			"void main(void) 																\n"
			"{																				\n"
			"	gl_Position = transform_mat * position;										\n"
			"	vs_color = color;															\n"
			"}																				\n"
		};

		//=====Texture Shader=====
		//This is used when the pirmitive to be drawn has a texture
		//to be drawn with it
		static const GLchar* _vertexShaderSourceTexture[] =
		{
			"#version 430 core																\n"
			"																				\n"
			"layout (location = 0) in vec4 position;										\n"
			"layout (location = 1) in vec2 tex_coord; 										\n"					
			"uniform mat4 transform_mat;													\n"
			"																				\n"
			"out vec2 vs_tex_coord;															\n"
			"																				\n"
			"void main(void) 																\n"
			"{																				\n"
			"	gl_Position = transform_mat * position;										\n"
			"	vs_tex_coord = vec2(tex_coord.x, 1.0f - tex_coord.y);						\n"
			"}																				\n"
		};

		//=====Fragment Shaders=====
		//=====Color Shader=====
		//This is used when only colors, not textures are used to render
		//a pirmitive
		static const GLchar* _fragmentShaderSourceColor[] = 
		{
			"#version 430 core																\n"
			"																				\n"
			"in vec4 vs_color;															\n"
			"out vec4 color;																\n"
			"																				\n"
			"void main(void) 																\n"
			"{																				\n"
			"	color = vs_color;															\n"
			"}																				\n"
		};

		//=====Texture Shader=====
		//This is used when the pirmitive to be drawn has a texture
		//to be drawn with it
		static const GLchar* _fragmentShaderSourceTexture[] =
		{
			"#version 430 core																\n"
			"																				\n"
			"uniform sampler2D ourTexture;													\n"
			"in vec2 vs_tex_coord;															\n"
			"out vec4 color;																\n"
			"																				\n"
			"void main(void) 																\n"
			"{																				\n"
			//=====test for textures, failed finish later=====
			//"	color = texelFetch(sampler, ivec2(gl_FragCoord.xy), 0);						\n"
			"	color = texture(ourTexture, vs_tex_coord);									\n"
			"}																				\n"
		};

		//=====Create and compile vertext shader=====
		GLuint vertexShaderProgramColor;
		GLuint vertexShaderProgramTexture;
		GLuint fragmentShaderProgramColor;
		GLuint fragmentShaderProgramTexture;

		//=====Compiled vertex shaders=====
		//=====Color=====
		vertexShaderProgramColor = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderProgramColor, 1, _vertexShaderSourceColor, NULL);
		glCompileShader(vertexShaderProgramColor);

		//=====Texutre=====
		vertexShaderProgramTexture = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderProgramTexture, 1, _vertexShaderSourceTexture, NULL);
		glCompileShader(vertexShaderProgramTexture);

		//=====Compile fragment shaders=====
		//=====Color=====
		fragmentShaderProgramColor = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderProgramColor, 1, _fragmentShaderSourceColor, NULL);
		glCompileShader(fragmentShaderProgramColor);

		//=====Texture=====
		fragmentShaderProgramTexture = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderProgramTexture, 1, _fragmentShaderSourceTexture, NULL);
		glCompileShader(fragmentShaderProgramTexture);

		//=====Create Color Shader, attach shader to it and link it=====
		_renderingProgramColor = glCreateProgram();
		glAttachShader(_renderingProgramColor, vertexShaderProgramColor);
		glAttachShader(_renderingProgramColor, fragmentShaderProgramColor);
		glLinkProgram(_renderingProgramColor);

		//=====Create Texture Shader, attach shader to it and link it=====
		_renderingProgramTexture = glCreateProgram();
		glAttachShader(_renderingProgramTexture, vertexShaderProgramTexture);
		glAttachShader(_renderingProgramTexture, fragmentShaderProgramTexture);
		glLinkProgram(_renderingProgramTexture);

		//=====Delete the sahders as the program now has them=====
		glDeleteShader(vertexShaderProgramColor);
		glDeleteShader(fragmentShaderProgramColor);
		glDeleteShader(vertexShaderProgramTexture);
		glDeleteShader(fragmentShaderProgramTexture);
	}

//=======================================================================================================
//_SetOrthoProjection
//=======================================================================================================
	void Renderer::_SetOrthoProjection(void) 
	{
		matrix projection{};
		projection.MakeOrthographic(1024, 768, 200);

		matrix model(1.0f);

		matrix final = projection * model;

		const F32* data = final.GetElems();

		//=====Color Shader setup=====
		glUseProgram(_renderingProgramColor);

		GLint transform1 = glGetUniformLocation(_renderingProgramColor, "transform_mat");

		glUniformMatrix4fv(transform1, 1, GL_FALSE, data);

		glUseProgram(0);

		//=====Texture Shader setup=====
		glUseProgram(_renderingProgramTexture);

		GLint transform2 = glGetUniformLocation(_renderingProgramTexture, "transform_mat");

		glUniformMatrix4fv(transform2, 1, GL_FALSE, data);

		glUseProgram(0);
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

//==========================================================================================================================
//
//Renderer Funtions
//
//==========================================================================================================================
//=======================================================================================================
//AddTri
//=======================================================================================================
	void Renderer::AddTri(const Cell& cell) 
	{
		if(_totalVerticesInBatch >= _maxBatchSize) { Draw(); }

		point pos = cell.GetPosition();
		color col = cell.GetColor();

		//=====First Vertext=====
		_triVerticies.push_back(pos.GetX() + cell.GetLeft());
		_triVerticies.push_back(pos.GetY() + cell.GetBottom());
		_triVerticies.push_back(pos.GetZ());
		_triVerticies.push_back(pos.GetW());
		
		++_totalVerticesInBatch;
		++_triBatch;
		
		//=====Second Vertex=====
		_triVerticies.push_back(pos.GetX() + cell.GetRight());
		_triVerticies.push_back(pos.GetY() + cell.GetBottom());
		_triVerticies.push_back(pos.GetZ());
		_triVerticies.push_back(pos.GetW());
		
		++_totalVerticesInBatch;
		++_triBatch;

		//=====Third Vertex=====
		_triVerticies.push_back(pos.GetX());
		_triVerticies.push_back(pos.GetY() + cell.GetTop());
		_triVerticies.push_back(pos.GetZ());
		_triVerticies.push_back(pos.GetW());
		
		++_totalVerticesInBatch;
		++_triBatch;

		//=====First Color=====
		_triColors.push_back(col.GetRed());
		_triColors.push_back(col.GetGreen());
		_triColors.push_back(col.GetBlue());
		_triColors.push_back(col.GetAlpha());

		//=====Second Color=====
		_triColors.push_back(col.GetRed());
		_triColors.push_back(col.GetGreen());
		_triColors.push_back(col.GetBlue());
		_triColors.push_back(col.GetAlpha());
		
		//=====Third Color=====
		_triColors.push_back(col.GetRed());
		_triColors.push_back(col.GetGreen());
		_triColors.push_back(col.GetBlue());
		_triColors.push_back(col.GetAlpha());

		
	}

//=======================================================================================================
//AddSqr
//=======================================================================================================
	void Renderer::AddSqr(const Cell& cell) 
	{
		if(_totalVerticesInBatch >= _maxBatchSize) { Draw(); }

		point pos = cell.GetPosition();
		color col = cell.GetColor();

		//=====First Vertex=====
		_sqrVertices.push_back(pos.GetX() + cell.GetLeft());
		_sqrVertices.push_back(pos.GetY() + cell.GetBottom());
		_sqrVertices.push_back(pos.GetZ());
		_sqrVertices.push_back(pos.GetW());

		//=====First Color=====
		_sqrColors.push_back(col.GetRed());
		_sqrColors.push_back(col.GetGreen());
		_sqrColors.push_back(col.GetBlue());
		_sqrColors.push_back(col.GetAlpha());

		++_totalVerticesInBatch;
		++_sqrBatch;

		//=====Second Vertex=====
		_sqrVertices.push_back(pos.GetX() + cell.GetRight());
		_sqrVertices.push_back(pos.GetY() + cell.GetBottom());
		_sqrVertices.push_back(pos.GetZ());
		_sqrVertices.push_back(pos.GetW());

		//=====Second Color=====
		_sqrColors.push_back(col.GetRed());
		_sqrColors.push_back(col.GetGreen());
		_sqrColors.push_back(col.GetBlue());
		_sqrColors.push_back(col.GetAlpha());
		
		++_totalVerticesInBatch;
		++_sqrBatch;

		//=====Third Vertex=====
		_sqrVertices.push_back(pos.GetX() + cell.GetLeft());
		_sqrVertices.push_back(pos.GetY() + cell.GetTop());
		_sqrVertices.push_back(pos.GetZ());
		_sqrVertices.push_back(pos.GetW());

		//=====Third Color=====
		_sqrColors.push_back(col.GetRed());
		_sqrColors.push_back(col.GetGreen());
		_sqrColors.push_back(col.GetBlue());
		_sqrColors.push_back(col.GetAlpha());

		++_totalVerticesInBatch;
		++_sqrBatch;

		//=====Fourth Vertex=====
		_sqrVertices.push_back(pos.GetX() + cell.GetRight());
		_sqrVertices.push_back(pos.GetY() + cell.GetTop());
		_sqrVertices.push_back(pos.GetZ());
		_sqrVertices.push_back(pos.GetW());

		//=====Fourth Color	=====
		_sqrColors.push_back(col.GetRed());
		_sqrColors.push_back(col.GetGreen());
		_sqrColors.push_back(col.GetBlue());
		_sqrColors.push_back(col.GetAlpha());

		++_totalVerticesInBatch;
		++_sqrBatch;

		//=====Fifth Vertex=====
		_sqrVertices.push_back(pos.GetX() + cell.GetRight());
		_sqrVertices.push_back(pos.GetY() + cell.GetBottom());
		_sqrVertices.push_back(pos.GetZ());
		_sqrVertices.push_back(pos.GetW());

		//=====Fifth Color=====
		_sqrColors.push_back(col.GetRed());
		_sqrColors.push_back(col.GetGreen());
		_sqrColors.push_back(col.GetBlue());
		_sqrColors.push_back(col.GetAlpha());

		++_totalVerticesInBatch;
		++_sqrBatch;


		//=====Sixth Vertex=====
		_sqrVertices.push_back(pos.GetX() + cell.GetLeft());
		_sqrVertices.push_back(pos.GetY() + cell.GetTop());
		_sqrVertices.push_back(pos.GetZ());
		_sqrVertices.push_back(pos.GetW());

		//=====Sixth Color	=====
		_sqrColors.push_back(col.GetRed());
		_sqrColors.push_back(col.GetGreen());
		_sqrColors.push_back(col.GetBlue());
		_sqrColors.push_back(col.GetAlpha());

		++_totalVerticesInBatch;
		++_sqrBatch;
	}

//=======================================================================================================
//AddHex
//=======================================================================================================
	void Renderer::AddHex(const Cell& cell) 
	{
		if(_totalVerticesInBatch >= _maxBatchSize) { Draw(); }

		point pos = cell.GetPosition();
		color col = cell.GetColor();

		//Triangle 1
		_hexVertices.push_back(pos.GetX());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + (cell.GetLeft() / 2 ));
		_hexVertices.push_back(pos.GetY() + cell.GetTop());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + (cell.GetRight() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetTop());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		//Triangle 2
		_hexVertices.push_back(pos.GetX());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + (cell.GetRight() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetTop());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + cell.GetRight());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		//Triangle 3
		_hexVertices.push_back(pos.GetX());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + cell.GetRight());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + (cell.GetRight() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetBottom());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		//Triangle 4
		_hexVertices.push_back(pos.GetX());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + (cell.GetRight() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetBottom());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + (cell.GetLeft() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetBottom());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		//Triangle 5
		_hexVertices.push_back(pos.GetX());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + (cell.GetLeft() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetBottom());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + cell.GetLeft());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		//Triangle 6
		_hexVertices.push_back(pos.GetX());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + cell.GetLeft());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		_hexVertices.push_back(pos.GetX() + (cell.GetLeft() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetTop());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;
		
	/*
		This is a version that will only work after I learn how to use draw multi array
		Triangle fan version of the hex pirmitive. Needs the draw multi array function 
		or one hex will stretch into another. 

		//Center Vertex
		_hexVertices.push_back(pos.GetX());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		//TopLeft
		_hexVertices.push_back(pos.GetX() + (cell.GetLeft() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetTop());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		//Top Right
		_hexVertices.push_back(pos.GetX() + (cell.GetRight() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetTop());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;
		
		//Right
		_hexVertices.push_back(pos.GetX() + cell.GetRight());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		//Bottom Right
		_hexVertices.push_back(pos.GetX() + (cell.GetRight() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetBottom());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;
		
		//Bottom Left
		_hexVertices.push_back(pos.GetX() + (cell.GetLeft() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetBottom());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;
		
		//Left
		_hexVertices.push_back(pos.GetX() + cell.GetLeft());
		_hexVertices.push_back(pos.GetY());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;

		//TopLeft
		_hexVertices.push_back(pos.GetX() + (cell.GetLeft() / 2));
		_hexVertices.push_back(pos.GetY() + cell.GetTop());
		_hexVertices.push_back(pos.GetZ());
		_hexVertices.push_back(pos.GetW());

		++_totalVerticesInBatch;
		++_hexBatch;
		

		//Center Color
		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

	*/

		//=====Colors=====

		//=====First Triangle color=====
		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());
		
		//=====Second Triangle Color=====
		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());
		
		//=====Third Triangle Color=====
		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());
		
		//=====Fourth Triangle Color=====
		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());
		
		//=====Fifth Triangle Colo=====
		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());
		
		//=====Sixth Triangel Color=====
		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());

		_hexColors.push_back(col.GetRed());
		_hexColors.push_back(col.GetGreen());
		_hexColors.push_back(col.GetBlue());
		_hexColors.push_back(col.GetAlpha());
	}

//=======================================================================================================
//AddTexturedTri
//=======================================================================================================
	void Renderer::AddTexturedTri(const Cell& cell, const Texture& texture) 
	{
		if(_totalVerticesInBatch >= _maxBatchSize) { Draw(); }

		GLuint currentTextureId = _textureManager->GetCurrentTextureId();

		if(texture.GetId() != currentTextureId) { _textureManager->SetCurrentTextureId(texture.GetId()); }

		AddTri(cell);

		//=====Bottom Left=====
		_triUVs.push_back(0.0f);
		_triUVs.push_back(0.0f);

		//=====Bottom Right=====
		_triUVs.push_back(1.0f);
		_triUVs.push_back(0.0f);

		//=====Top=====
		_triUVs.push_back(0.5f);
		_triUVs.push_back(1.0f);
	}

//=======================================================================================================
//AddTexturedSqr
//=======================================================================================================
	void Renderer::AddTexturedSqr(const Cell& cell, const Texture& texture) 
	{
		if(_totalVerticesInBatch >= _maxBatchSize) { Draw(); }

		GLuint currentTextureId = _textureManager->GetCurrentTextureId();

		if(texture.GetId() != currentTextureId) 
		{ 
			Draw();
			_textureManager->SetCurrentTextureId(texture.GetId()); 
		}

		AddSqr(cell);

		//=====UVs=====
		//=====Bottom Left=====
		_sqrUVs.push_back(0.0f);
		_sqrUVs.push_back(0.0f);

		//=====Bottom Right=====
		_sqrUVs.push_back(1.0f);
		_sqrUVs.push_back(0.0f);

		//=====Top Left=====
		_sqrUVs.push_back(0.0f);
		_sqrUVs.push_back(1.0f);
		
		//=====Top Right=====
		_sqrUVs.push_back(1.0f);
		_sqrUVs.push_back(1.0f);

		//=====Bottom Right=====
		_sqrUVs.push_back(1.0f);
		_sqrUVs.push_back(0.0f);

		//=====Top Left=====
		_sqrUVs.push_back(0.0f);
		_sqrUVs.push_back(1.0f);

	}

//=======================================================================================================
//AddTexturedHex
//=======================================================================================================
	void Renderer::AddTexturedHex(const Cell& cell, const Texture& texture) 
	{
		if(_totalVerticesInBatch >= _maxBatchSize) { Draw(); }

		AddHex(cell);
	}

//=======================================================================================================
//Draw
//=======================================================================================================
	void Renderer::Draw(void) 
	{
		if(_totalVerticesInBatch == 0) { return; } //End if there are no verticies to draw

		glUseProgram(0);	
		
		 if(_triBatch > 0) 
		 {
		    
		    if(_triUVs.size() <= 0) 
		    {

			    glUseProgram(_renderingProgramColor);

				GLuint buffers[2];

				glGenBuffers(2, buffers);

				glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _triVerticies.size()), &_triVerticies[0], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _triColors.size()), &_triColors[0], GL_STATIC_DRAW);
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(1);

				
				glDrawArrays(GL_TRIANGLES, 0, _triBatch);
			}
			else if(_triUVs.size() >= 1) 
			{
				glUseProgram(_renderingProgramTexture);

				GLuint buffers[2];

				glGenBuffers(2, buffers);

				glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _triVerticies.size()), &_triVerticies[0], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _triUVs.size()), &_triUVs[0], GL_STATIC_DRAW);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(1);

				glDrawArrays(GL_TRIANGLES, 0, _triBatch);
			}
		}

		if(_sqrBatch > 0) 
		{
		    
		    if(_sqrUVs.size() == 0) 
		    {
			    glUseProgram(_renderingProgramColor);

				GLuint buffers[2];
				glGenBuffers(2, buffers);

				glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _sqrVertices.size()), &_sqrVertices[0], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _sqrColors.size()), &_sqrColors[0], GL_STATIC_DRAW);
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(1);
				
				glDrawArrays(GL_TRIANGLES, 0, _sqrBatch);
			}

			else if(_sqrUVs.size() >= 1) 
			{

				glUseProgram(_renderingProgramTexture);

				GLuint buffers[2];
				glGenBuffers(2, buffers);

				glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _sqrVertices.size()), &_sqrVertices[0], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _sqrUVs.size()), &_sqrUVs[0], GL_STATIC_DRAW);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				glEnableVertexAttribArray(1);

				glDrawArrays(GL_TRIANGLES, 0, _sqrBatch);

				glDeleteBuffers(2, buffers);

			}	
		}

		if(_hexBatch > 0) 
		{
		    glUseProgram(_renderingProgramColor);

			GLuint buffers[2];
			glGenBuffers(2, buffers);

			glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _hexVertices.size()), &_hexVertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _hexColors.size()), &_hexColors[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(1);
			
			glDrawArrays(GL_TRIANGLES, 0, _hexBatch);
		}



		//=====Reset All Containers and Counters=====
			_triVerticies.clear();
			_triColors.clear();
			_triUVs.clear();
			_sqrVertices.clear();
			_sqrColors.clear();
			_sqrUVs.clear();
			_hexVertices.clear();
			_hexColors.clear();

			_totalVerticesInBatch = 0;
			_triBatch = 0;
			_sqrBatch = 0;
			_hexBatch = 0; 
	}

//=======================================================================================================
//
//Constructor
//
//=======================================================================================================
	Renderer::Renderer(void): _maxBatchSize(1000), 
							  _totalVerticesInBatch(0),
							  _triBatch(0),
							  _sqrBatch(0),
							  _hexBatch(0), 
							  _errorManager(ErrorManager::Instance()),
							  _textureManager(TextureManager::Instance()),
							  _programWindow(ProgramWindow::Instance()) 
	{ 
		_CompileShaders();
		glGenVertexArrays(1, &_vertexArrayObject);
		glBindVertexArray(_vertexArrayObject);
		_SetOrthoProjection();
	}

}//End namespace		