#include <Engine/TriSprite.h>
#include <iostream>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	TriSprite::TriSprite(void)
	{
		v_InitShader();
	}

	TriSprite::~TriSprite(void) {  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void TriSprite::v_RenderSprite(void)
	{
		//v_SetVertexPositions();

		//Array ver = Sprite::GetVertices();

		//std::cout << "Sprite ver: " << ver[0] << ":" << ver[1] << ":" << ver[2] << "\n";

		//Renderer::Instance()->AddToBatch(Sprite::GetVertices(), Sprite::GetVertexColors());

		//std::cout << "I am render\n" << _shaderProgram << "\n" << Sprite::GetPosition().GetX() << ":" << GetWidth() << "\n"
		//		  << GetHeight() << ":" << GetHeight() << "\n" << GetColor().GetRed() << ":" << GetColor().GetGreen() << ":" << GetColor().GetBlue() << "\n\n";

		Renderer::Instance()->AddToBatch(_shaderProgram, Sprite::GetPosition(), Sprite::GetWidth(), Sprite::GetHeight(), Sprite::GetColor());
	}

	void TriSprite::v_SetVertexPositions(void)
	{
		Array vertices = Sprite::GetVertices();

		vertices.clear();

		F32 xOffset = Sprite::GetWidth() / 2;
		F32 yOffset = Sprite::GetHeight() / 2;
		F32 xPos = Sprite::GetPosition().GetX();
		F32 yPos = Sprite::GetPosition().GetY();
		F32 zPos = Sprite::GetPosition().GetZ();
		F32 wPos = Sprite::GetPosition().GetW();

		//=====Top=====		
		vertices.push_back(xPos);
		vertices.push_back(yPos + yOffset);
		vertices.push_back(zPos);
		vertices.push_back(wPos);

		//=====Bottom Left=====
		vertices.push_back(xPos - xOffset);
		vertices.push_back(yPos - yOffset);
		vertices.push_back(zPos);
		vertices.push_back(wPos);

		//=====Bottom Right=====
		vertices.push_back(xPos + xOffset);
		vertices.push_back(yPos - yOffset);
		vertices.push_back(zPos);
		vertices.push_back(wPos);

		Sprite::SetVertices(vertices);
	}

	void TriSprite::v_SetVertexColors(void)
	{
		Array colors = Sprite::GetVertexColors();
		colors.clear();

		F32 R = Sprite::GetColor().GetRed();
		F32 G = Sprite::GetColor().GetGreen();
		F32 B = Sprite::GetColor().GetBlue();
		F32 A = Sprite::GetColor().GetAlpha();

		//=====Top=====
		colors.push_back(R);
		colors.push_back(G);
		colors.push_back(B);
		colors.push_back(A);

		//=====Bottom Left=====
		colors.push_back(R);
		colors.push_back(G);
		colors.push_back(B);
		colors.push_back(A);

		//=====Bottom Right=====
		colors.push_back(R);
		colors.push_back(G);
		colors.push_back(B);
		colors.push_back(A);

		Sprite::SetVertexColors(colors);
	}

	void TriSprite::v_SetPosition(Vec2& position)
	{
		Sprite::SetPosition(position);
		v_SetVertexPositions();
	}

	void TriSprite::v_SetColor(Col& col)
	{
		Sprite::SetColor(col);
		v_SetVertexColors();
	}

	GLuint TriSprite::_shaderProgram = NULL;
	GLuint TriSprite::v_GetShader(void)
	{
		if(_shaderProgram == NULL) { v_InitShader(); }
		return _shaderProgram;
	}	

	void TriSprite::v_InitShader(void)
	{
		if(_shaderProgram != NULL) return;
		
		//=====Vertex Shaders=====
		//This is used when only colors, not textures are used to render
		//a pirmitive
		static const GLchar* _vertexShaderSource[] = 
		{
			"#version 430 core																\n"
			"																				\n"
			"layout (location = 0) in vec4 position;										\n"
			"layout (location = 1) in vec4 color; 											\n"
			"layout (location = 2) in float width; 											\n"
			"layout (location = 3) in float height; 										\n"					
			"uniform mat4 transform_mat;													\n"
			"																				\n"
			"out vec4 vs_color;																\n"
			"out vec4 vs_dimnsions;															\n"
			"																				\n"
			"void main(void) 																\n"
			"{																				\n"
			//=====Top=====
			"	gl_Position = transform_mat * position;										\n"
			"	vs_color = color;															\n"
			"	vs_dimnsions = vec4(width, height, 0.0, 0.0);								\n"
			"}																				\n"
		};

		//=====Geomtry Shader=====
		static const GLchar* _geometryShaderSource[] =
		{
			"#version 430 core 																\n"
			"																				\n"
			"layout(points) in; 															\n"
			"layout(triangle_strip, max_vertices = 2) out;									\n"
			"																				\n"
			"in vec4 vs_color[1]; 															\n"
			"in vec4 vs_dimnsions[1]; 														\n"
			"																				\n"
			"out vec4 gs_color; 															\n"
			"																				\n"
			"void main()																	\n"
			"{																				\n"
			//Bottom Left
			" 	gl_Position = gl_in[0].gl_Position + vec4(-vs_dimnsions[0].x, -vs_dimnsions[0].y, 0.0, 0.0); 	\n"
			"	EmitVertex();				 																	\n"
			//Top
			"	gl_Position = gl_in[0].gl_Position + vec4(0.0, vs_dimnsions[0].y, 0.0, 0.0);					\n"
			"	EmitVertex(); 																					\n"
			//Bottom Right
			"	gl_Position = gl_in[0].gl_Position + vec4(vs_dimnsions[0].x, -vs_dimnsions[0].y, 0, 0);			\n"
			" 	EmitVertex(); 																					\n"
			"																				\n"
			"	EndPrimitive(); 															\n"
			"	gs_color = vs_color[0]; 													\n"
			"}																				\n"
		};


		//=====Fragment Shaders=====
		//This is used when only colors, not textures are used to render
		//a pirmitive
		static const GLchar* _fragmentShaderSource[] = 
		{
			"#version 430 core																\n"
			"																				\n"
			"in vec4 gs_color;																\n"
			"out vec4 color;																\n"
			"																				\n"
			"void main(void) 																\n"
			"{																				\n"
			"	color = gs_color;															\n"
			"}																				\n"
		};

		//=====Compile Shaders=====
		GLuint vertextShaderProgram;
		GLuint geometryShaderProgram;
		GLuint fragmentShaderProgram;

		vertextShaderProgram = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertextShaderProgram, 1, _vertexShaderSource, NULL);
		glCompileShader(vertextShaderProgram);

		geometryShaderProgram = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShaderProgram, 1, _geometryShaderSource, NULL);
		glCompileShader(geometryShaderProgram);

		fragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderProgram, 1, _fragmentShaderSource, NULL);
		glCompileShader(fragmentShaderProgram);

		_shaderProgram = glCreateProgram();
		glAttachShader(_shaderProgram, vertextShaderProgram);
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
		glDeleteShader(vertextShaderProgram);
		glDeleteShader(geometryShaderProgram);
		glDeleteShader(vertextShaderProgram);
	}
	
}//end namespace
