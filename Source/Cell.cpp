#include <Cell.h>

//---------------------------------------------------------------------------------------------Constructor
Cell::Cell() {}

//----------------------------------------------------------------------------------------------------Init
bool Cell::Init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

//------------------------------------------------------------------------------------------------ShutDown
void Cell::ShutDown() {}

//-------------------------------------------------------------------------------------------------Prepare
void Cell::Prepare() {

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

//--------------------------------------------------------------------------------------------------Render
void Cell::Render() {
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &_vertices[0]);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, &_indices[0]);
	glDisableClientState(GL_VERTEX_ARRAY);*/
}