#include <Renderer.h>

//-------------------------------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------------------------------
Renderer::Renderer(void) {
	_maxVerticies = 1000;
	_verticies    = new Point<>[_maxVerticies];
	_colors       = new Color<>[_maxVerticies];
	_uvs          = new GLfloat[_maxVerticies];
	_batchSize    = 0;
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
void Renderer::AddCell(Cell &cell) {
	if(_batchSize + cell.TotalVertices() > _maxVerticies) { Render(); }

	for(U32 i = 0; i < cell.TotalPositions(); i++) {
		_verticies[_batchSize] = cell.VertexPositions()[i];
		_colors[_batchSize]    = cell.VertexColors()[i];
		_batchSize++;
	}
}

//-------------------------------------------------------------------------------------------------------
//SetPointers
//-------------------------------------------------------------------------------------------------------
void Renderer::SetPointers(void) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &_verticies[0]);

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, &_colors[0]); 
}


//-------------------------------------------------------------------------------------------------------
//Render
//-------------------------------------------------------------------------------------------------------
void Renderer::Render(void) {
	if(_batchSize == 0) { return; } //End if there are no verticies to draw

	SetPointers();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //view port set up
    glTranslatef(0.0f, 0.0f, -20.0f);
	
	glDrawArrays(GL_TRIANGLES, 0, _batchSize);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	_batchSize = 0;
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