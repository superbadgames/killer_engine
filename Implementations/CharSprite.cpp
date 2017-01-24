#include <Engine/CharSprite.h>
#include <iostream>

namespace KillerEngine
{
	CharSprite::CharSprite(void) : _charX(0), _charY(0), _charWidth(0), _charHeight(0), _xoffset(0), _yoffset(0), _xadvance(0)
	{
		v_InitShader();
	}

	CharSprite::CharSprite(U32 x, U32 y, U32 width, U32 height, U32 xoffset, U32 yoffset, U32 xadvance) 
						     :_charX(0), _charY(0), _charWidth(0), _charHeight(0), _xoffset(0), _yoffset(0), _xadvance(0)
	{  }

//==========================================================================================================================
//
//Virtual Functions 	 	
//
//==========================================================================================================================
	void CharSprite::v_RenderSprite(void)
	{
		//Renderer::Instance()->AddToBatch(Sprite::vertexPositions, Sprite::vertexColors);
		Renderer::Instance()->AddToBatch(_shaderProgram, Sprite::GetPosition(), Sprite::GetWidth(), Sprite::GetHeight(), Sprite::GetColor(), 
							   			 Sprite::GetTextureID(), Sprite::GetUVOrigin(), Sprite::GetUVLimit());
		//std::cout << "char sprite render\n";
		//Renderer::Instance()->AddToBatch(_shaderProgram, Sprite::GetPosition(), Sprite::GetWidth(), Sprite::GetHeight(), Sprite::GetColor());
	}

	GLuint CharSprite::_shaderProgram = NULL;
	GLuint CharSprite::v_GetShader(void)
	{
		if(_shaderProgram == NULL) { v_InitShader(); }
		return _shaderProgram;
	}

/*
	void CharSprite::v_SetTextureCoords(const F32 top, const F32 bottom, const F32 right, const F32 left)
	{
		Sprite::vertexUvs.clear();

		//=====Vertices=====
		//=====Triangle1=====
		//top right
		_vertexUvs.push_back(right);
		_vertexUvs.push_back(top);

		//bottom right
		_vertexUvs.push_back(right);
		_vertexUvs.push_back(bottom);

		//bottom left
		_vertexUvs.push_back(left);
		_vertexUvs.push_back(bottom);

		//=====Triangle2=====
		//top right
		_vertexUvs.push_back(right);
		_vertexUvs.push_back(top);

		//top left
		_vertexUvs.push_back(left);
		_vertexUvs.push_back(top);

		//bottom left
		_vertexUvs.push_back(left);
		_vertexUvs.push_back(bottom);
	}
*/
//==========================================================================================================================
//Shader
//==========================================================================================================================
	void CharSprite::v_InitShader(void)
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
			"layout (location = 3) in vec2 uvOrigin;										\n"
			"layout (location = 4) in vec2 uvLimit;											\n"

			"uniform mat4 transform_mat;													\n"
			
			"out vec4 gs_color;																\n"
			"out vec4 gs_dimensions;														\n"
			"out vec2 gs_uvOrigin;															\n"
			"out vec2 gs_uvLimit;"

			"void main(void) 																\n"
			"{																				\n"
			"	gl_Position = transform_mat * position;										\n"
			"	gs_color = color;															\n"
			"	gs_dimensions = transform_mat * vec4(dimensions.x, dimensions.y, 0.0, 0.0);	\n"
			"	gs_uvOrigin = uvOrigin;														\n"
			"	gs_uvLimit = uvLimit;														\n"
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
			"in vec2 gs_uvOrigin[];															\n"
			"in vec2 gs_uvLimit[];															\n"
			
			"out vec4 fs_color; 															\n"
			"out vec2 fs_uvs;															\n"
			
			"void main()																	\n"
			"{																				\n"
			//Bottom Right
			"	fs_uvs = vec2(gs_uvOrigin[0].x, gs_uvLimit[0].y);												\n"
			"	fs_color = gs_color[0];																			\n"
			"	gl_Position = gl_in[0].gl_Position + vec4(-gs_dimensions[0].x, -gs_dimensions[0].y, 0, 0);		\n"
			" 	EmitVertex(); 																					\n"
			//Top Right
			"	fs_uvs = vec2(gs_uvLimit[0].x, gs_uvOrigin[0].y);												\n"
			"	fs_color = gs_color[0];																			\n"
			"	gl_Position = gl_in[0].gl_Position + vec4(-gs_dimensions[0].x, gs_dimensions[0].y, 0.0, 0.0);	\n"
			"	EmitVertex(); 																					\n"
			//Bottom Left
			"	fs_uvs = vec2(gs_uvLimit[0].x, gs_uvLimit[0].y);												\n"
			"	fs_color = gs_color[0];																			\n"
			" 	gl_Position = gl_in[0].gl_Position + vec4(gs_dimensions[0].x, -gs_dimensions[0].y, 0.0, 0.0); 	\n"
			"	EmitVertex();				 																	\n"
			//Top Left
			"	fs_uvs = vec2(gs_uvLimit[0].x, gs_uvOrigin[0].y);												\n"
			"	fs_color = gs_color[0];																			\n"
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
	
			"uniform sampler2D tex;													\n"
			"in vec4 fs_color;																\n"
			"in vec2 fs_uvs;																\n"
			"out vec4 color;"
			
			"void main(void) 																\n"
			"{																				\n"
			"	color = texture(tex, fs_uvs);										\n"
			//"	breakgl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);															\n"
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