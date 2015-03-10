#include <Renderer.h>

//-----------------------------------------------------------------------------------------------Constructor
Renderer::Renderer(void) {
	_maxVerticies = 1000;
	_verticies    = new F32[_maxVerticies];
	_colors       = new F32[_maxVerticies];
	_uvs          = new F32[_maxVerticies];
}

//---------------------------------------------------------------------------------------------------Instance
//--Static Member Declaration
Renderer* Renderer::_instance = NULL;
Renderer* Renderer::Instance(void) {
	if(_instance == NULL) { _instance = new Renderer(); }

	return _instance;
}

//----------------------------------------------------------------------------------------------------AddCell
void Renderer::AddCell(void) {
	//Implemenat later
}

//------------------------------------------------------------------------------------------------SetPointers
void Renderer::SetPointers(void) {
	//Reset Screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &_verticies);

}

//-----------------------------------------------------------------------------------------------------Render
void Renderer::Render(void) {
	if(_batchSize == 0) { return; } //End if there are no verticies to draw

	Renderer::SetPointers();
	
	glDrawArrays(GL_TRIANGLES, 0, _batchSize);
	_batchSize = 0;

	glDisableClientState(GL_VERTEX_ARRAY);
}

//---------------------------------------------------------------------------------------------------ShutDown
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