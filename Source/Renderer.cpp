#include <Renderer.h>

Renderer::Renderer() {
	m_rotationAngle = 0.0f;
}

bool Renderer::init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

void Renderer::Prepare(F32 dt) {
	/*-------------------------------------------Triangle example
	const F32 SPEED = 15.0f;
	m_rotationAngle += SPEED * dt;

	if(m_rotationAngle > 360.0f) { m_rotationAngle -= 360.0f; }-------------*/

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Pairs of 3 will be in an XYZ format
	//bottom left
	_vertices.push_back(-2.0f);
	_vertices.push_back(-2.0f);
	_vertices.push_back(0.0f);

	//bottom right
	_vertices.push_back(2.0f);
	_vertices.push_back(-2.0f);
	_vertices.push_back(0.0f);

	//top right
	_vertices.push_back(2.0f);
	_vertices.push_back(2.0f);
	_vertices.push_back(0.0f);

	//top left
	_vertices.push_back(-2.0f);
	_vertices.push_back(2.0f);
	_vertices.push_back(0.0f);

	//Specify indices for triangles
	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(3);

	_indices.push_back(1);
	_indices.push_back(2);
	_indices.push_back(3);

}

void Renderer::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);
	
	/*------------------------------------------------Triangle example chp 2
	glRotatef(m_rotationAngle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -2.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -2.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.5f, -2.0f);
	glEnd();-----------------------------------*/

	//------------------------------------------------Square example, chp 3
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &_vertices[0]);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, &_indices[0]);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Renderer::ShutDown() {}