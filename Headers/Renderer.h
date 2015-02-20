#ifndef RENDERER_H
#define RENDERER_H
//Killer1 inlucdes
#include <Atom.h>

//3rd party includes
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>


class Renderer {
public:
	Renderer();

	bool init();
	void Prepare(F32 dt);
	void Render();
	void ShutDown();

	void OnResize(int width, int height);

private:
	F32 		     m_rotationAngle;
	std::vector<F32> _vertices;
	std::vector<GLuint> _indices;
};

#endif