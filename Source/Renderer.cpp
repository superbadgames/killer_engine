#include <Renderer.h>

//=======================================================================================================
//
//Constructor
//
//=======================================================================================================
Renderer::Renderer(void): _maxBatchSize(1000), _totalVerticesInBatch(0) { 
	_renderingProgram = _CompileShaders();
	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);
}

//=======================================================================================================
//
//Instance
//
//=======================================================================================================
//=====Static Member Declaration=====
Renderer* Renderer::_instance;

Renderer* Renderer::Instance(void) {
	if(_instance == NULL) { _instance = new Renderer(); }

	return _instance;
}

//=======================================================================================================
//
//Add*
//
//There is an Add function for Triangles, Squares and Hexagons. These are:
//AddTri()
//AddSqr()
//AddHex()
//
//These take the position of a cell, then create F32 points, storing them in an std::vector, which is 
//passed to OGL during the Draw().  
//
//=======================================================================================================
void Renderer::AddTri(const Cell& cell) {
	if(_totalVerticesInBatch >= _maxBatchSize) { Draw(); }

	point pos = cell.GetPosition();
	color col = cell.GetColor();

	//First Vertext
	_triVerticies.push_back(pos.GetX() + cell.GetLeft());
	_triVerticies.push_back(pos.GetY() + cell.GetBottom());
	_triVerticies.push_back(pos.GetZ());
	_triVerticies.push_back(pos.GetW());
	
	++_totalVerticesInBatch;
	++_triBatch;
	
	//Second Vertex
	_triVerticies.push_back(pos.GetX() + cell.GetRight());
	_triVerticies.push_back(pos.GetY() + cell.GetBottom());
	_triVerticies.push_back(pos.GetZ());
	_triVerticies.push_back(pos.GetW());
	
	++_totalVerticesInBatch;
	++_triBatch;

	//Third Vertex
	_triVerticies.push_back(pos.GetX());
	_triVerticies.push_back(pos.GetY() + cell.GetTop());
	_triVerticies.push_back(pos.GetZ());
	_triVerticies.push_back(pos.GetW());
	
	++_totalVerticesInBatch;
	++_triBatch;

	//First Color
	_triColors.push_back(col.GetRed());
	_triColors.push_back(col.GetGreen());
	_triColors.push_back(col.GetBlue());
	_triColors.push_back(col.GetAlpha());

	//Second Color
	_triColors.push_back(col.GetRed());
	_triColors.push_back(col.GetGreen());
	_triColors.push_back(col.GetBlue());
	_triColors.push_back(col.GetAlpha());
	
	//Third Color
	_triColors.push_back(col.GetRed());
	_triColors.push_back(col.GetGreen());
	_triColors.push_back(col.GetBlue());
	_triColors.push_back(col.GetAlpha());

	
}

void Renderer::AddSqr(const Cell& cell) {
	if(_totalVerticesInBatch >= _maxBatchSize) { Draw(); }

	point pos = cell.GetPosition();
	color col = cell.GetColor();

	//First Vertex
	_sqrVertices.push_back(pos.GetX() + cell.GetLeft());
	_sqrVertices.push_back(pos.GetY() + cell.GetBottom());
	_sqrVertices.push_back(pos.GetZ());
	_sqrVertices.push_back(pos.GetW());

	++_totalVerticesInBatch;
	++_sqrBatch;

	//Second Vertex
	_sqrVertices.push_back(pos.GetX() + cell.GetRight());
	_sqrVertices.push_back(pos.GetY() + cell.GetBottom());
	_sqrVertices.push_back(pos.GetZ());
	_sqrVertices.push_back(pos.GetW());
	
	++_totalVerticesInBatch;
	++_sqrBatch;

	//Third Vertex
	_sqrVertices.push_back(pos.GetX() + cell.GetLeft());
	_sqrVertices.push_back(pos.GetY() + cell.GetTop());
	_sqrVertices.push_back(pos.GetZ());
	_sqrVertices.push_back(pos.GetW());

	++_totalVerticesInBatch;
	++_sqrBatch;

	//Fourth Vertex
	_sqrVertices.push_back(pos.GetX() + cell.GetRight());
	_sqrVertices.push_back(pos.GetY() + cell.GetTop());
	_sqrVertices.push_back(pos.GetZ());
	_sqrVertices.push_back(pos.GetW());

	++_totalVerticesInBatch;
	++_sqrBatch;

	//Fifth Vertex
	_sqrVertices.push_back(pos.GetX() + cell.GetRight());
	_sqrVertices.push_back(pos.GetY() + cell.GetBottom());
	_sqrVertices.push_back(pos.GetZ());
	_sqrVertices.push_back(pos.GetW());

	++_totalVerticesInBatch;
	++_sqrBatch;


	//Sixth Vertex
	_sqrVertices.push_back(pos.GetX() + cell.GetLeft());
	_sqrVertices.push_back(pos.GetY() + cell.GetTop());
	_sqrVertices.push_back(pos.GetZ());
	_sqrVertices.push_back(pos.GetW());

	++_totalVerticesInBatch;
	++_sqrBatch;

	//First Color
	_sqrColors.push_back(col.GetRed());
	_sqrColors.push_back(col.GetGreen());
	_sqrColors.push_back(col.GetBlue());
	_sqrColors.push_back(col.GetAlpha());

	//Second Color
	_sqrColors.push_back(col.GetRed());
	_sqrColors.push_back(col.GetGreen());
	_sqrColors.push_back(col.GetBlue());
	_sqrColors.push_back(col.GetAlpha());

	//Third Color
	_sqrColors.push_back(col.GetRed());
	_sqrColors.push_back(col.GetGreen());
	_sqrColors.push_back(col.GetBlue());
	_sqrColors.push_back(col.GetAlpha());

	//Fourth Color	
	_sqrColors.push_back(col.GetRed());
	_sqrColors.push_back(col.GetGreen());
	_sqrColors.push_back(col.GetBlue());
	_sqrColors.push_back(col.GetAlpha());

	//Fifth Color	
	_sqrColors.push_back(col.GetRed());
	_sqrColors.push_back(col.GetGreen());
	_sqrColors.push_back(col.GetBlue());
	_sqrColors.push_back(col.GetAlpha());

	//Sixth Color	
	_sqrColors.push_back(col.GetRed());
	_sqrColors.push_back(col.GetGreen());
	_sqrColors.push_back(col.GetBlue());
	_sqrColors.push_back(col.GetAlpha());

	

}

void Renderer::AddHex(const Cell& cell) {
	if(_totalVerticesInBatch >= _maxBatchSize) { Draw(); }

	point pos = cell.GetPosition();
	color col = cell.GetColor();

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

	//First color
	_hexColors.push_back(col.GetRed());
	_hexColors.push_back(col.GetGreen());
	_hexColors.push_back(col.GetBlue());
	_hexColors.push_back(col.GetAlpha());
	
	//Second Color
	_hexColors.push_back(col.GetRed());
	_hexColors.push_back(col.GetGreen());
	_hexColors.push_back(col.GetBlue());
	_hexColors.push_back(col.GetAlpha());
	
	//Third Color
	_hexColors.push_back(col.GetRed());
	_hexColors.push_back(col.GetGreen());
	_hexColors.push_back(col.GetBlue());
	_hexColors.push_back(col.GetAlpha());
	
	//Fourth Color
	_hexColors.push_back(col.GetRed());
	_hexColors.push_back(col.GetGreen());
	_hexColors.push_back(col.GetBlue());
	_hexColors.push_back(col.GetAlpha());
	
	//Fifth Color
	_hexColors.push_back(col.GetRed());
	_hexColors.push_back(col.GetGreen());
	_hexColors.push_back(col.GetBlue());
	_hexColors.push_back(col.GetAlpha());
	
	//Sixth Color
	_hexColors.push_back(col.GetRed());
	_hexColors.push_back(col.GetGreen());
	_hexColors.push_back(col.GetBlue());
	_hexColors.push_back(col.GetAlpha());

	//Sixth Color
	_hexColors.push_back(col.GetRed());
	_hexColors.push_back(col.GetGreen());
	_hexColors.push_back(col.GetBlue());
	_hexColors.push_back(col.GetAlpha());
	
}

//=======================================================================================================
//
//Draw
//
//=======================================================================================================
void Renderer::Draw(void) {
	if(_totalVerticesInBatch == 0) { return; } //End if there are no verticies to draw
	
	 if(_triBatch > 0) {
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		const GLfloat color[] = { 0.5, 0.5, 0.5, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

	    glUseProgram(_renderingProgram);

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

	if(_sqrBatch > 0) {
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		const GLfloat color[] = { 0.5, 0.5, 0.5, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

	    glUseProgram(_renderingProgram);

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

	if(_hexBatch > 0) {
		
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		const GLfloat color[] = { 0.5, 0.5, 0.5, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

	    glUseProgram(_renderingProgram);

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
		
		glDrawArrays(GL_TRIANGLE_FAN, 0, _hexBatch);
	}

	//Reset Batch count
		_totalVerticesInBatch = 0;
}

//====================================================
//_CompileShaders
//====================================================

GLuint Renderer::_CompileShaders(void){
	GLuint vertexShaderProgram;
	GLuint tessControlProgram;
	GLuint tessEvalProgram;
	GLuint fragmentShaderProgram;
	GLuint finalProgram;

	//=====Vertex Shader=====
	//=====Vertex Shader=====
	static const GLchar* _vertexShaderSource[] = {
		"#version 430 core													\n"
		"																	\n"
		"layout (location = 0) in vec4 position;							\n"
		"layout (location = 1) in vec4 color; 								\n"
		"																	\n"
		"out vec4 vs_color;													\n"
		"																	\n"
		"void main(void){													\n"
		"	gl_Position = position;											\n"
		"	vs_color = color; 												\n"
		"}																	\n"
	};

	//=====Tesselsation Control Shader=====
	static const GLchar* _tessControlSource[] = {
		"#version 430 core 																\n"
		"																				\n"
		"layout (vertices = 3) out;			 											\n"
		"																				\n"
		"void main(void) {																\n"	
		"	if(gl_InvocationID == 0) {													\n"
		"		gl_TessLevelInner[0] = 5.0;		 										\n"
		"		gl_TessLevelOuter[0] = 5.0;												\n"
		"		gl_TessLevelOuter[1] = 5.0;												\n"
		"		gl_TessLevelOuter[2] = 5.0;												\n"
		"	} 																			\n"
		"	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position; 	\n"
		"} 																				\n"
		
	};

	//=====Tesselsation Evaluation Shader=====
	static const GLchar* _tessEvalShaderSource[] = {
		"#version 430 core 																\n"
		"																				\n"
		"layout (triangles, equal_spacing, cw) in; 										\n"
		"																				\n"
		"void main(void) {																\n"
		"	gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +						\n"
		"				   gl_TessCoord.y * gl_in[1].gl_Position +						\n"
		"				   gl_TessCoord.z * gl_in[2].gl_Position);						\n"
		"}																			 	\n"
	};

	//=====Fragment Shader=====
	static const GLchar* _fragmentShaderSource[] = {
		"#version 430 core								\n"
		"												\n"
		"in vec4 vs_color;								\n"
		"out vec4 color;								\n"
		"												\n"
		"void main(void) {								\n"
		"	color = vs_color;							\n"
		"}												\n"
	};


	//=====Create and compile vertext shader=====
	vertexShaderProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderProgram, 1, _vertexShaderSource, NULL);
	glCompileShader(vertexShaderProgram);

	//=====Create and compile tessellation control shader=====
	tessControlProgram = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(tessControlProgram, 1, _tessControlSource, NULL);
	glCompileShader(tessControlProgram);

	//======Create and comple tessellation evaluation shader=====
	tessEvalProgram = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(tessEvalProgram, 1, _tessEvalShaderSource, NULL);
	glCompileShader(tessEvalProgram);

	//=====Create and compile fragment shader=====
	fragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderProgram, 1, _fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderProgram);

	//=====Create program, attach shader to it and link it=====
	finalProgram = glCreateProgram();
	glAttachShader(finalProgram, vertexShaderProgram);
	//glAttachShader(finalProgram, tessControlProgram);
	//glAttachShader(finalProgram, tessEvalProgram);
	glAttachShader(finalProgram, fragmentShaderProgram);
	glLinkProgram(finalProgram);

	//=====Delete the sahders as the program now has them=====
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(tessControlProgram);
	glDeleteShader(tessEvalProgram);
	glDeleteShader(fragmentShaderProgram);

	return finalProgram;
}

//====================================================
//_SetOrthoProjection
//====================================================
void Renderer::_SetOrthoProjection(void) {
	matrix M1{};
	M1.MakeOrthographic(1072, 768, 200);

	const F32* projection = M1.GetElems();

	glUniformMatrix4fv(0, 1, GL_FALSE, projection);
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