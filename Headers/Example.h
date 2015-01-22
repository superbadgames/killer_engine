#ifndef EXAMPLE_H
#define EXAMPLE_H
//Killer1 inlucdes
#include <Atom.h>

//3rd party includes
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>


class Example {
public:
	Example();

	bool init();
	void Prepare(F32 dt);
	void Render();
	void ShutDown();

	void OnResize(int width, int height);

private:
	F32 m_rotationAngle;
};

#endif