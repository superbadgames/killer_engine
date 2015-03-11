#include <Renderer.h>

//-------------------------------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------------------------------
Renderer::Renderer(void) {
	_maxVerticies = 1000;
	_verticies    = new GLfloat[_maxVerticies];
	_colors       = new F32[_maxVerticies];
	_uvs          = new F32[_maxVerticies];
}

//-------------------------------------------------------------------------------------------------------
//Instance
//-------------------------------------------------------------------------------------------------------
//--Static Member Declaration
Renderer* Renderer::_instance = NULL;

Renderer* Renderer::Instance(void) {
	if(_instance == NULL) { _instance = new Renderer(); }

	return _instance;
}

//-------------------------------------------------------------------------------------------------------
//AddCell
//-------------------------------------------------------------------------------------------------------
void Renderer::AddCell(void) {

glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

//triangle 1
	_verticies[0] = -0.50f;
	_verticies[1] = -0.50f;
	_verticies[2] =  0.0f;

	_verticies[3] = 0.50f;
	_verticies[4] = -0.50f;
	_verticies[5] = 0.0f;

	_verticies[6] = -0.50f;
	_verticies[7] = 0.50f;
	_verticies[8] = 0.0f;
//triangle 2
	_verticies[9] = 0.50f;
	_verticies[10] = -0.50f;
	_verticies[11] = 0.0f;

	_verticies[12] = 0.50f;
	_verticies[13] = 0.50f;
	_verticies[14] = 0.0f;

	_verticies[15] = -0.50f;
	_verticies[16] = 0.50f;
	_verticies[17] = 0.0f;

}

//-------------------------------------------------------------------------------------------------------
//SetPointers
//-------------------------------------------------------------------------------------------------------
void Renderer::SetPointers(void) {
	F32 newcolor[] {1.0f, 0.0f, 0.0f}; 





	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &_verticies[0]);

//	glEnableClientState(GL_COLOR_ARRAY);
//	glColorPointer(3, GL_FLOAT, 0, &newcolor[0]); 

	


	//glGenBuffers(1, &_vertexBuffer);
	//glBindBuffers(GL_ARRAY_BUFFER, _vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, &_verticies[0], GL_STATIC_DRAW);

}


//-------------------------------------------------------------------------------------------------------
//Render
//-------------------------------------------------------------------------------------------------------
void Renderer::Render(void) {
	//if(_batchSize == 0) { return; } //End if there are no verticies to draw

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //view port set up
    glTranslatef(0.0f, 0.0f, -20.0f);

    SetPointers();

    //glVertexPointer(3, GL_FLOAT, 0, 0);

    //glEnableClientState(GL_VERTEX_ARRAY);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glColor3f(0.5f, 0.0f, 0.0f);
	
	glDrawArrays(GL_TRIANGLES, 0, 18);
	glDisableClientState(GL_VERTEX_ARRAY);

	//_batchSize = 0;
}

//-------------------------------------------------------------------------------------------------------
//ShutDown
//-------------------------------------------------------------------------------------------------------
void Renderer::ShutDown(void) {
	delete _verticies;
	delete _colors;
	delete _uvs;
	delete _instance;
}

/*
glClearColor(1.0, 1.0, 1.0);
this needs to become the backgraound color
*/