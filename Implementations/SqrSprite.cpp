#include <Engine/SqrSprite.h>
#include <iostream>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================		
		SqrSprite::SqrSprite(void)
		{
			v_InitShader();
		}

		SqrSprite::~SqrSprite(void) {  }

//==========================================================================================================================
//
//Virtual Functions 	 	
//
//==========================================================================================================================
	void SqrSprite::v_RenderSprite(void)
	{
		Renderer::Instance()->AddToBatch(_shaderProgram, Sprite::GetPosition(), Sprite::GetWidth(), Sprite::GetHeight(), Sprite::GetColor());
	}

	GLuint SqrSprite::_shaderProgram = NULL;
	GLuint SqrSprite::v_GetShader(void)
	{
		if(_shaderProgram == NULL) { v_InitShader(); }
		return _shaderProgram;
	}

//==========================================================================================================================
//Shader
//==========================================================================================================================
	void SqrSprite::v_InitShader(void)
	{
		if(_shaderProgram != NULL) return;

		//=====Vertex Shaders=====
		//This is used when only colors, not textures are used to render
		//a pirmitive
		static const GLchar* _vertexShaderSource[] = 
		{
			"#version 430 core																\n"
			
			"layout (location = 0) in vec4 position;										\n"
			"layout (location = 1) in vec4 color; 											\n"
			"layout (location = 2) in vec2 dimensions;										\n"

			"uniform mat4 transform_mat;													\n"
			
			"out vec4 gs_color;																\n"
			"out vec4 gs_dimensions;														\n"
			
			"void main(void) 																\n"
			"{																				\n"
			"	gl_Position = transform_mat * position;										\n"
			"	gs_color = color;															\n"
			"	gs_dimensions = transform_mat * vec4(dimensions.x, dimensions.y, 0.0, 0.0);	\n"
			"}																				\n"
		};



		//=====Geomtry Shader=====
		static const GLchar* _geometryShaderSource[] =
		{
			"#version 430 core 																\n"
			
			"layout(points) in; 															\n"
			"layout(triangle_strip, max_vertices = 6) out;									\n"
			
			"in vec4 gs_color[]; 															\n"
			"in vec4 gs_dimensions[]; 														\n"
			
			"out vec4 fs_color; 															\n"
			
			"void main()																	\n"
			"{																				\n"
			"	fs_color = gs_color[0]; 													\n"
			//Bottom Right
			"	gl_Position = gl_in[0].gl_Position + vec4(-gs_dimensions[0].x, -gs_dimensions[0].y, 0, 0);		\n"
			" 	EmitVertex(); 																					\n"
			//Top Right
			"	gl_Position = gl_in[0].gl_Position + vec4(-gs_dimensions[0].x, gs_dimensions[0].y, 0.0, 0.0);	\n"
			"	EmitVertex(); 																					\n"
			//Bottom Left
			" 	gl_Position = gl_in[0].gl_Position + vec4(gs_dimensions[0].x, -gs_dimensions[0].y, 0.0, 0.0); 	\n"
			"	EmitVertex();				 																	\n"
			//Top Left
			"	gl_Position = gl_in[0].gl_Position + vec4(gs_dimensions[0].x, gs_dimensions[0].y, 0, 0); 		\n"
			"	EmitVertex(); 																					\n"
			
			"	EndPrimitive(); 															\n"
			"}																				\n"
		};


		//=====Fragment Shaders=====
		//This is used when only colors, not textures are used to render
		//a pirmitive
		static const GLchar* _fragmentShaderSource[] = 
		{
			"#version 430 core																\n"
	
			"in vec4 fs_color;																\n"
			"out vec4 color;																\n"
			
			"void main(void) 																\n"
			"{																				\n"
			"	color = fs_color;															\n"
			"}																				\n"
		};


		//=====Compile Shaders=====
		GLuint vertexShaderProgram;
		GLuint geometryShaderProgram;
		GLuint fragmentShaderProgram;

		vertexShaderProgram = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderProgram, 1, _vertexShaderSource, NULL);
		glCompileShader(vertexShaderProgram);

		geometryShaderProgram = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShaderProgram, 1, _geometryShaderSource, NULL);
		glCompileShader(geometryShaderProgram);

		fragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderProgram, 1, _fragmentShaderSource, NULL);
		glCompileShader(fragmentShaderProgram);

		//=====Link=====
		_shaderProgram = glCreateProgram();
		glAttachShader(_shaderProgram, vertexShaderProgram);
		glAttachShader(_shaderProgram, geometryShaderProgram);
		glAttachShader(_shaderProgram, fragmentShaderProgram);
		glLinkProgram(_shaderProgram);

		GLint isLinked = 0;
		glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &isLinked);

		//=====Error Checking=====
		if(isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_shaderProgram, maxLength, &maxLength, &infoLog[0]);

			for(auto i = infoLog.begin(); i != infoLog.end(); ++i)
			{
				std::cout << *i ;
			}

			std::cout << "\n";

			//The program is useless now. So delete it.
			glDeleteProgram(_shaderProgram);

		}

		//=====Clean up=====
		glDeleteShader(vertexShaderProgram);
		glDeleteShader(geometryShaderProgram);
		glDeleteShader(fragmentShaderProgram);
	}
}//end namespace